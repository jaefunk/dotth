﻿
#include "D3D11Shader.h"

///////////////////////////////////////////////////////////////////////////////
// ------ BASE SIMPLE SHADER --------------------------------------------------
///////////////////////////////////////////////////////////////////////////////

// --------------------------------------------------------
// Constructor accepts DirectX device & context
// --------------------------------------------------------
ISimpleShader::ISimpleShader(ID3D11Device* device, ID3D11DeviceContext* context)
{
	// Save the device
	this->device = device;
	this->deviceContext = context;

	// Set up fields
	constantBufferCount = 0;
	constantBuffers = 0;
	shaderBlob = 0;
}

// --------------------------------------------------------
// Destructor
// --------------------------------------------------------
ISimpleShader::~ISimpleShader()
{
	// Derived class destructors will call this class's CleanUp method
	if (shaderBlob)
		shaderBlob->Release();
}

// --------------------------------------------------------
// Cleans up the variable table and buffers - Some things will
// be handled by derived classes
// --------------------------------------------------------
void ISimpleShader::CleanUp()
{
	// Handle constant buffers and local data buffers
	for (unsigned int i = 0; i < constantBufferCount; i++)
	{
		constantBuffers[i].ConstantBuffer->Release();
		delete[] constantBuffers[i].LocalDataBuffer;
	}

	if (constantBuffers)
	{
		delete[] constantBuffers;
		constantBufferCount = 0;
	}

	for (unsigned int i = 0; i < shaderResourceViews.size(); i++)
		delete shaderResourceViews[i];

	for (unsigned int i = 0; i < samplerStates.size(); i++)
		delete samplerStates[i];

	// Clean up tables
	varTable.clear();
	cbTable.clear();
	samplerTable.clear();
	textureTable.clear();
}

// --------------------------------------------------------
// Loads the specified shader and builds the variable table using shader
// reflection.  This must be a separate step from the constructor since
// we can't invoke derived class overrides in the base class constructor.
//
// shaderFile - A "wide string" specifying the compiled shader to load
// 
// Returns true if shader is loaded properly, false otherwise
// --------------------------------------------------------
bool ISimpleShader::LoadShaderFile(LPCWSTR shaderFile)
{
	// Load the shader to a blob and ensure it worked
	HRESULT hr = D3DReadFileToBlob(shaderFile, &shaderBlob);
	if (hr != S_OK)
	{
		return false;
	}

	// Create the shader - Calls an overloaded version of this abstract
	// method in the appropriate child class
	shaderValid = CreateShader(shaderBlob);
	if (!shaderValid)
	{
		return false;
	}

	// Set up shader reflection to get information about
	// this shader and its variables,  buffers, etc.
	ID3D11ShaderReflection* refl;
	D3DReflect(
		shaderBlob->GetBufferPointer(),
		shaderBlob->GetBufferSize(),
		IID_ID3D11ShaderReflection,
		(void**)&refl);

	// Get the description of the shader
	D3D11_SHADER_DESC shaderDesc;
	refl->GetDesc(&shaderDesc);

	// Create resource arrays
	constantBufferCount = shaderDesc.ConstantBuffers;
	constantBuffers = new SimpleConstantBuffer[constantBufferCount];

	// Handle bound resources (like shaders and samplers)
	unsigned int resourceCount = shaderDesc.BoundResources;
	for (unsigned int r = 0; r < resourceCount; r++)
	{
		// Get this resource's description
		D3D11_SHADER_INPUT_BIND_DESC resourceDesc;
		refl->GetResourceBindingDesc(r, &resourceDesc);

		// Check the type
		switch (resourceDesc.Type)
		{
		case D3D_SIT_TEXTURE: // A texture resource
		{
			// Create the SRV wrapper
			SimpleSRV* srv = new SimpleSRV();
			srv->BindIndex = resourceDesc.BindPoint;	// Shader bind point
			srv->Index = static_cast<unsigned int>(shaderResourceViews.size());	// Raw index

			textureTable.insert(std::pair<std::string, SimpleSRV*>(resourceDesc.Name, srv));
			shaderResourceViews.push_back(srv);
		}
		break;

		case D3D_SIT_SAMPLER: // A sampler resource
		{
			// Create the sampler wrapper
			SimpleSampler* samp = new SimpleSampler();
			samp->BindIndex = resourceDesc.BindPoint;	// Shader bind point
			samp->Index = static_cast<unsigned int>(samplerStates.size());			// Raw index

			samplerTable.insert(std::pair<std::string, SimpleSampler*>(resourceDesc.Name, samp));
			samplerStates.push_back(samp);
		}
		break;
		}
	}

	// Loop through all constant buffers
	for (unsigned int b = 0; b < constantBufferCount; b++)
	{
		// Get this buffer
		ID3D11ShaderReflectionConstantBuffer* cb =
			refl->GetConstantBufferByIndex(b);

		// Get the description of this buffer
		D3D11_SHADER_BUFFER_DESC bufferDesc;
		cb->GetDesc(&bufferDesc);

		// Get the description of the resource binding, so
		// we know exactly how it's bound in the shader
		D3D11_SHADER_INPUT_BIND_DESC bindDesc;
		refl->GetResourceBindingDescByName(bufferDesc.Name, &bindDesc);

		// Set up the buffer and put its pointer in the table
		constantBuffers[b].BindIndex = bindDesc.BindPoint;
		constantBuffers[b].Name = bufferDesc.Name;
		cbTable.insert(std::pair<std::string, SimpleConstantBuffer*>(bufferDesc.Name, &constantBuffers[b]));

		// Create this constant buffer
		D3D11_BUFFER_DESC newBuffDesc;
		newBuffDesc.Usage = D3D11_USAGE_DEFAULT;
		newBuffDesc.ByteWidth = bufferDesc.Size;
		newBuffDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		newBuffDesc.CPUAccessFlags = 0;
		newBuffDesc.MiscFlags = 0;
		newBuffDesc.StructureByteStride = 0;
		device->CreateBuffer(&newBuffDesc, 0, &constantBuffers[b].ConstantBuffer);

		// Set up the data buffer for this constant buffer
		constantBuffers[b].Size = bufferDesc.Size;
		constantBuffers[b].LocalDataBuffer = new unsigned char[bufferDesc.Size];
		ZeroMemory(constantBuffers[b].LocalDataBuffer, bufferDesc.Size);

		// Loop through all variables in this buffer
		for (unsigned int v = 0; v < bufferDesc.Variables; v++)
		{
			// Get this variable
			ID3D11ShaderReflectionVariable* var =
				cb->GetVariableByIndex(v);

			// Get the description of the variable and its type
			D3D11_SHADER_VARIABLE_DESC varDesc;
			var->GetDesc(&varDesc);

			// Create the variable struct
			SimpleShaderVariable varStruct;
			varStruct.ConstantBufferIndex = b;
			varStruct.ByteOffset = varDesc.StartOffset;
			varStruct.Size = varDesc.Size;

			// Get a string version
			std::string varName(varDesc.Name);

			// Add this variable to the table and the constant buffer
			varTable.insert(std::pair<std::string, SimpleShaderVariable>(varName, varStruct));
			constantBuffers[b].Variables.push_back(varStruct);
		}
	}

	// All set
	refl->Release();
	return true;
}

// --------------------------------------------------------
// Helper for looking up a variable by name and also
// verifying that it is the requested size
// 
// name - the name of the variable to look for
// size - the size of the variable (for verification), or -1 to bypass
// --------------------------------------------------------
SimpleShaderVariable* ISimpleShader::FindVariable(std::string name, int size)
{
	// Look for the key
	std::unordered_map<std::string, SimpleShaderVariable>::iterator result =
		varTable.find(name);

	// Did we find the key?
	if (result == varTable.end())
		return 0;

	// Grab the result from the iterator
	SimpleShaderVariable* var = &(result->second);

	// Is the data size correct ?
	if (size > 0 && var->Size != size)
		return 0;

	// Success
	return var;
}

// --------------------------------------------------------
// Helper for looking up a constant buffer by name
// --------------------------------------------------------
SimpleConstantBuffer* ISimpleShader::FindConstantBuffer(std::string name)
{
	// Look for the key
	std::unordered_map<std::string, SimpleConstantBuffer*>::iterator result =
		cbTable.find(name);

	// Did we find the key?
	if (result == cbTable.end())
		return 0;

	// Success
	return result->second;
}

// --------------------------------------------------------
// Sets the shader and associated constant buffers in DirectX
// --------------------------------------------------------
void ISimpleShader::SetShader()
{
	// Ensure the shader is valid
	if (!shaderValid) return;

	// Set the shader and any relevant constant buffers, which
	// is an overloaded method in a subclass
	SetShaderAndCBs();
}

// --------------------------------------------------------
// Copies the relevant data to the all of this 
// shader's constant buffers.  To just copy one
// buffer, use CopyBufferData()
// --------------------------------------------------------
void ISimpleShader::CopyAllBufferData()
{
	// Ensure the shader is valid
	if (!shaderValid) return;

	// Loop through the constant buffers and copy all data
	for (unsigned int i = 0; i < constantBufferCount; i++)
	{
		// Copy the entire local data buffer
		deviceContext->UpdateSubresource(
			constantBuffers[i].ConstantBuffer, 0, 0,
			constantBuffers[i].LocalDataBuffer, 0, 0);
	}
}

// --------------------------------------------------------
// Copies local data to the shader's specified constant buffer
//
// index - The index of the buffer to copy.
//         Useful for updating more frequently-changing
//         variables without having to re-copy all buffers.
//  
// NOTE: The "index" of the buffer might NOT be the same
//       as its register, especially if you have buffers
//       bound to non-sequential registers!
// --------------------------------------------------------
void ISimpleShader::CopyBufferData(unsigned int index)
{
	// Ensure the shader is valid
	if (!shaderValid) return;

	// Validate the index
	if (index >= this->constantBufferCount)
		return;

	// Check for the buffer
	SimpleConstantBuffer* cb = &this->constantBuffers[index];
	if (!cb) return;

	// Copy the data and get out
	deviceContext->UpdateSubresource(
		cb->ConstantBuffer, 0, 0,
		cb->LocalDataBuffer, 0, 0);
}

// --------------------------------------------------------
// Copies local data to the shader's specified constant buffer
//
// bufferName - Specifies the name of the buffer to copy.
//              Useful for updating more frequently-changing
//              variables without having to re-copy all buffers.
// --------------------------------------------------------
void ISimpleShader::CopyBufferData(std::string bufferName)
{
	// Ensure the shader is valid
	if (!shaderValid) return;

	// Check for the buffer
	SimpleConstantBuffer* cb = this->FindConstantBuffer(bufferName);
	if (!cb) return;

	// Copy the data and get out
	deviceContext->UpdateSubresource(
		cb->ConstantBuffer, 0, 0,
		cb->LocalDataBuffer, 0, 0);
}


// --------------------------------------------------------
// Sets a variable by name with arbitrary data of the specified size
//
// name - The name of the shader variable
// data - The data to set in the buffer
// size - The size of the data (this must match the variable's size)
//
// Returns true if data is copied, false if variable doesn't 
// exist or sizes don't match
// --------------------------------------------------------
bool ISimpleShader::SetData(std::string name, const void* data, unsigned int size)
{
	// Look for the variable and verify
	SimpleShaderVariable* var = FindVariable(name, size);
	if (var == 0)
		return false;

	// Set the data in the local data buffer
	memcpy(
		constantBuffers[var->ConstantBufferIndex].LocalDataBuffer + var->ByteOffset,
		data,
		size);

	// Success
	return true;
}

// --------------------------------------------------------
// Sets INTEGER data
// --------------------------------------------------------
bool ISimpleShader::SetInt(std::string name, int data)
{
	return this->SetData(name, (void*)(&data), sizeof(int));
}

// --------------------------------------------------------
// Sets a FLOAT variable by name in the local data buffer
// --------------------------------------------------------
bool ISimpleShader::SetFloat(std::string name, float data)
{
	return this->SetData(name, (void*)(&data), sizeof(float));
}

// --------------------------------------------------------
// Sets a FLOAT2 variable by name in the local data buffer
// --------------------------------------------------------
bool ISimpleShader::SetFloat2(std::string name, const float data[2])
{
	return this->SetData(name, (void*)data, sizeof(float) * 2);
}

// --------------------------------------------------------
// Sets a FLOAT2 variable by name in the local data buffer
// --------------------------------------------------------
bool ISimpleShader::SetFloat2(std::string name, const DirectX::XMFLOAT2 data)
{
	return this->SetData(name, &data, sizeof(float) * 2);
}

// --------------------------------------------------------
// Sets a FLOAT3 variable by name in the local data buffer
// --------------------------------------------------------
bool ISimpleShader::SetFloat3(std::string name, const float data[3])
{
	return this->SetData(name, (void*)data, sizeof(float) * 3);
}

// --------------------------------------------------------
// Sets a FLOAT3 variable by name in the local data buffer
// --------------------------------------------------------
bool ISimpleShader::SetFloat3(std::string name, const DirectX::XMFLOAT3 data)
{
	return this->SetData(name, &data, sizeof(float) * 3);
}

// --------------------------------------------------------
// Sets a FLOAT4 variable by name in the local data buffer
// --------------------------------------------------------
bool ISimpleShader::SetFloat4(std::string name, const float data[4])
{
	return this->SetData(name, (void*)data, sizeof(float) * 4);
}

// --------------------------------------------------------
// Sets a FLOAT4 variable by name in the local data buffer
// --------------------------------------------------------
bool ISimpleShader::SetFloat4(std::string name, const DirectX::XMFLOAT4 data)
{
	return this->SetData(name, &data, sizeof(float) * 4);
}

// --------------------------------------------------------
// Sets a MATRIX (4x4) variable by name in the local data buffer
// --------------------------------------------------------
bool ISimpleShader::SetMatrix4x4(std::string name, const float data[16])
{
	return this->SetData(name, (void*)data, sizeof(float) * 16);
}

// --------------------------------------------------------
// Sets a MATRIX (4x4) variable by name in the local data buffer
// --------------------------------------------------------
bool ISimpleShader::SetMatrix4x4(std::string name, const DirectX::XMFLOAT4X4 data)
{
	return this->SetData(name, &data, sizeof(float) * 16);
}

// --------------------------------------------------------
// Gets info about a shader variable, if it exists
// --------------------------------------------------------
const SimpleShaderVariable* ISimpleShader::GetVariableInfo(std::string name)
{
	return FindVariable(name, -1);
}

// --------------------------------------------------------
// Gets info about an SRV in the shader (or null)
//
// name - the name of the SRV
// --------------------------------------------------------
const SimpleSRV* ISimpleShader::GetShaderResourceViewInfo(std::string name)
{
	// Look for the key
	std::unordered_map<std::string, SimpleSRV*>::iterator result =
		textureTable.find(name);

	// Did we find the key?
	if (result == textureTable.end())
		return 0;

	// Success
	return result->second;
}


// --------------------------------------------------------
// Gets info about an SRV in the shader (or null)
//
// index - the index of the SRV
// --------------------------------------------------------
const SimpleSRV* ISimpleShader::GetShaderResourceViewInfo(unsigned int index)
{
	// Valid index?
	if (index >= shaderResourceViews.size()) return 0;

	// Grab the bind index
	return shaderResourceViews[index];
}


// --------------------------------------------------------
// Gets info about a sampler in the shader (or null)
// 
// name - the name of the sampler
// --------------------------------------------------------
const SimpleSampler* ISimpleShader::GetSamplerInfo(std::string name)
{
	// Look for the key
	std::unordered_map<std::string, SimpleSampler*>::iterator result =
		samplerTable.find(name);

	// Did we find the key?
	if (result == samplerTable.end())
		return 0;

	// Success
	return result->second;
}

// --------------------------------------------------------
// Gets info about a sampler in the shader (or null)
// 
// index - the index of the sampler
// --------------------------------------------------------
const SimpleSampler* ISimpleShader::GetSamplerInfo(unsigned int index)
{
	// Valid index?
	if (index >= samplerStates.size()) return 0;

	// Grab the bind index
	return samplerStates[index];
}


// --------------------------------------------------------
// Gets the number of constant buffers in this shader
// --------------------------------------------------------
unsigned int ISimpleShader::GetBufferCount() { return constantBufferCount; }



// --------------------------------------------------------
// Gets the size of a particular constant buffer, or -1
// --------------------------------------------------------
unsigned int ISimpleShader::GetBufferSize(unsigned int index)
{
	// Valid index?
	if (index >= constantBufferCount)
		return -1;

	// Grab the size
	return constantBuffers[index].Size;
}

// --------------------------------------------------------
// Gets info about a particular constant buffer 
// by name, if it exists
// --------------------------------------------------------
const SimpleConstantBuffer* ISimpleShader::GetBufferInfo(std::string name)
{
	return FindConstantBuffer(name);
}

// --------------------------------------------------------
// Gets info about a particular constant buffer 
//
// index - the index of the constant buffer
// --------------------------------------------------------
const SimpleConstantBuffer* ISimpleShader::GetBufferInfo(unsigned int index)
{
	// Check for valid index
	if (index >= constantBufferCount) return 0;

	// Return the specific buffer
	return &constantBuffers[index];
}





///////////////////////////////////////////////////////////////////////////////
// ------ SIMPLE VERTEX SHADER ------------------------------------------------
///////////////////////////////////////////////////////////////////////////////

// --------------------------------------------------------
// Constructor just calls the base
// --------------------------------------------------------
SimpleVertexShader::SimpleVertexShader(ID3D11Device* device, ID3D11DeviceContext* context)
	: ISimpleShader(device, context)
{
	// Ensure we set to zero to successfully trigger
	// the Input Layout creation during LoadShader()
	this->inputLayout = 0;
	this->shader = 0;
	this->perInstanceCompatible = false;
}

// --------------------------------------------------------
// Constructor overload which takes a custom input layout
//
// Passing in a valid input layout will stop LoadShader()
// from creating an input layout from shader reflection
// --------------------------------------------------------
SimpleVertexShader::SimpleVertexShader(ID3D11Device* device, ID3D11DeviceContext* context, ID3D11InputLayout* inputLayout, bool perInstanceCompatible)
	: ISimpleShader(device, context)
{
	// Save the custom input layout
	this->inputLayout = inputLayout;
	this->shader = 0;

	// Unable to determine from an input layout, require user to tell us
	this->perInstanceCompatible = perInstanceCompatible;
}

// --------------------------------------------------------
// Destructor - Clean up actual shader (base will be called automatically)
// --------------------------------------------------------
SimpleVertexShader::~SimpleVertexShader()
{
	CleanUp();
}

// --------------------------------------------------------
// Handles cleaning up shader and base class clean up
// --------------------------------------------------------
void SimpleVertexShader::CleanUp()
{
	ISimpleShader::CleanUp();
	if (shader) { shader->Release(); shader = 0; }
	if (inputLayout) { inputLayout->Release(); inputLayout = 0; }
}

// --------------------------------------------------------
// Creates the DirectX vertex shader
//
// shaderBlob - The shader's compiled code
//
// Returns true if shader is created correctly, false otherwise
// --------------------------------------------------------
bool SimpleVertexShader::CreateShader(ID3DBlob* shaderBlob)
{
	// Clean up first, in the event this method is
	// called more than once on the same object
	this->CleanUp();

	// Create the shader from the blob
	HRESULT result = device->CreateVertexShader(
		shaderBlob->GetBufferPointer(),
		shaderBlob->GetBufferSize(),
		0,
		&shader);

	// Did the creation work?
	if (result != S_OK)
		return false;

	// Do we already have an input layout?
	// (This would come from one of the constructor overloads)
	if (inputLayout)
		return true;

	// Vertex shader was created successfully, so we now use the
	// shader code to re-reflect and create an input layout that 
	// matches what the vertex shader expects.  Code adapted from:
	// https://takinginitiative.wordpress.com/2011/12/11/directx-1011-basic-shader-reflection-automatic-input-layout-creation/

	// Reflect shader info
	ID3D11ShaderReflection* refl;
	D3DReflect(
		shaderBlob->GetBufferPointer(),
		shaderBlob->GetBufferSize(),
		IID_ID3D11ShaderReflection,
		(void**)&refl);

	// Get shader info
	D3D11_SHADER_DESC shaderDesc;
	refl->GetDesc(&shaderDesc);

	// Read input layout description from shader info
	std::vector<D3D11_INPUT_ELEMENT_DESC> inputLayoutDesc;
	for (unsigned int i = 0; i < shaderDesc.InputParameters; i++)
	{
		D3D11_SIGNATURE_PARAMETER_DESC paramDesc;
		refl->GetInputParameterDesc(i, &paramDesc);

		// Check the semantic name for "_PER_INSTANCE"
		std::string perInstanceStr = "_PER_INSTANCE";
		std::string sem = paramDesc.SemanticName;
		int lenDiff = static_cast<int>(sem.size() - perInstanceStr.size());
		bool isPerInstance =
			lenDiff >= 0 &&
			sem.compare(lenDiff, perInstanceStr.size(), perInstanceStr) == 0;

		// Fill out input element desc
		D3D11_INPUT_ELEMENT_DESC elementDesc;
		elementDesc.SemanticName = paramDesc.SemanticName;
		elementDesc.SemanticIndex = paramDesc.SemanticIndex;
		elementDesc.InputSlot = 0;
		elementDesc.AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
		elementDesc.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		elementDesc.InstanceDataStepRate = 0;

		// Replace anything affected by "per instance" data
		if (isPerInstance)
		{
			elementDesc.InputSlot = 1; // Assume per instance data comes from another input slot!
			elementDesc.InputSlotClass = D3D11_INPUT_PER_INSTANCE_DATA;
			elementDesc.InstanceDataStepRate = 1;

			perInstanceCompatible = true;
		}

		// Determine DXGI format
		if (paramDesc.Mask == 1)
		{
			if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32) elementDesc.Format = DXGI_FORMAT_R32_UINT;
			else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32) elementDesc.Format = DXGI_FORMAT_R32_SINT;
			else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32) elementDesc.Format = DXGI_FORMAT_R32_FLOAT;
		}
		else if (paramDesc.Mask <= 3)
		{
			if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32) elementDesc.Format = DXGI_FORMAT_R32G32_UINT;
			else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32) elementDesc.Format = DXGI_FORMAT_R32G32_SINT;
			else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32) elementDesc.Format = DXGI_FORMAT_R32G32_FLOAT;
		}
		else if (paramDesc.Mask <= 7)
		{
			if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32) elementDesc.Format = DXGI_FORMAT_R32G32B32_UINT;
			else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32) elementDesc.Format = DXGI_FORMAT_R32G32B32_SINT;
			else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32) elementDesc.Format = DXGI_FORMAT_R32G32B32_FLOAT;
		}
		else if (paramDesc.Mask <= 15)
		{
			if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32) elementDesc.Format = DXGI_FORMAT_R32G32B32A32_UINT;
			else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32) elementDesc.Format = DXGI_FORMAT_R32G32B32A32_SINT;
			else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32) elementDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		}

		// Save element desc
		inputLayoutDesc.push_back(elementDesc);
	}

	// Try to create Input Layout
	HRESULT hr = device->CreateInputLayout(
		&inputLayoutDesc[0],
		static_cast<unsigned int>(inputLayoutDesc.size()),
		shaderBlob->GetBufferPointer(),
		shaderBlob->GetBufferSize(),
		&inputLayout);

	// All done, clean up
	refl->Release();
	return true;
}

// --------------------------------------------------------
// Sets the vertex shader, input layout and constant buffers
// for future DirectX drawing
// --------------------------------------------------------
void SimpleVertexShader::SetShaderAndCBs()
{
	// Is shader valid?
	if (!shaderValid) return;

	// Set the shader and input layout
	deviceContext->IASetInputLayout(inputLayout);
	deviceContext->VSSetShader(shader, 0, 0);

	// Set the constant buffers
	for (unsigned int i = 0; i < constantBufferCount; i++)
	{
		deviceContext->VSSetConstantBuffers(
			constantBuffers[i].BindIndex,
			1,
			&constantBuffers[i].ConstantBuffer);
	}
}

// --------------------------------------------------------
// Sets a shader resource view in the vertex shader stage
//
// name - The name of the texture resource in the shader
// srv - The shader resource view of the texture in GPU memory
//
// Returns true if a texture of the given name was found, false otherwise
// --------------------------------------------------------
bool SimpleVertexShader::SetShaderResourceView(std::string name, ID3D11ShaderResourceView* srv)
{
	// Look for the variable and verify
	const SimpleSRV* srvInfo = GetShaderResourceViewInfo(name);
	if (srvInfo == 0)
		return false;

	// Set the shader resource view
	deviceContext->VSSetShaderResources(srvInfo->BindIndex, 1, &srv);

	// Success
	return true;
}

// --------------------------------------------------------
// Sets a sampler state in the vertex shader stage
//
// name - The name of the sampler state in the shader
// samplerState - The sampler state in GPU memory
//
// Returns true if a sampler of the given name was found, false otherwise
// --------------------------------------------------------
bool SimpleVertexShader::SetSamplerState(std::string name, ID3D11SamplerState* samplerState)
{
	// Look for the variable and verify
	const SimpleSampler* sampInfo = GetSamplerInfo(name);
	if (sampInfo == 0)
		return false;

	// Set the shader resource view
	deviceContext->VSSetSamplers(sampInfo->BindIndex, 1, &samplerState);

	// Success
	return true;
}


///////////////////////////////////////////////////////////////////////////////
// ------ SIMPLE PIXEL SHADER -------------------------------------------------
///////////////////////////////////////////////////////////////////////////////

// --------------------------------------------------------
// Constructor just calls the base
// --------------------------------------------------------
SimplePixelShader::SimplePixelShader(ID3D11Device* device, ID3D11DeviceContext* context)
	: ISimpleShader(device, context)
{
	this->shader = 0;
}

// --------------------------------------------------------
// Destructor - Clean up actual shader (base will be called automatically)
// --------------------------------------------------------
SimplePixelShader::~SimplePixelShader()
{
	CleanUp();
}

// --------------------------------------------------------
// Handles cleaning up shader and base class clean up
// --------------------------------------------------------
void SimplePixelShader::CleanUp()
{
	ISimpleShader::CleanUp();
	if (shader) { shader->Release(); shader = 0; }
}

// --------------------------------------------------------
// Creates the DirectX pixel shader
//
// shaderBlob - The shader's compiled code
//
// Returns true if shader is created correctly, false otherwise
// --------------------------------------------------------
bool SimplePixelShader::CreateShader(ID3DBlob* shaderBlob)
{
	// Clean up first, in the event this method is
	// called more than once on the same object
	this->CleanUp();

	// Create the shader from the blob
	HRESULT result = device->CreatePixelShader(
		shaderBlob->GetBufferPointer(),
		shaderBlob->GetBufferSize(),
		0,
		&shader);

	// Check the result
	return (result == S_OK);
}

// --------------------------------------------------------
// Sets the pixel shader and constant buffers for
// future DirectX drawing
// --------------------------------------------------------
void SimplePixelShader::SetShaderAndCBs()
{
	// Is shader valid?
	if (!shaderValid) return;

	// Set the shader
	deviceContext->PSSetShader(shader, 0, 0);

	// Set the constant buffers
	for (unsigned int i = 0; i < constantBufferCount; i++)
	{
		deviceContext->PSSetConstantBuffers(
			constantBuffers[i].BindIndex,
			1,
			&constantBuffers[i].ConstantBuffer);
	}
}

// --------------------------------------------------------
// Sets a shader resource view in the pixel shader stage
//
// name - The name of the texture resource in the shader
// srv - The shader resource view of the texture in GPU memory
//
// Returns true if a texture of the given name was found, false otherwise
// --------------------------------------------------------
bool SimplePixelShader::SetShaderResourceView(std::string name, ID3D11ShaderResourceView* srv)
{
	// Look for the variable and verify
	const SimpleSRV* srvInfo = GetShaderResourceViewInfo(name);
	if (srvInfo == 0)
		return false;

	// Set the shader resource view
	deviceContext->PSSetShaderResources(srvInfo->BindIndex, 1, &srv);

	// Success
	return true;
}

// --------------------------------------------------------
// Sets a sampler state in the pixel shader stage
//
// name - The name of the sampler state in the shader
// samplerState - The sampler state in GPU memory
//
// Returns true if a sampler of the given name was found, false otherwise
// --------------------------------------------------------
bool SimplePixelShader::SetSamplerState(std::string name, ID3D11SamplerState* samplerState)
{
	// Look for the variable and verify
	const SimpleSampler* sampInfo = GetSamplerInfo(name);
	if (sampInfo == 0)
		return false;

	// Set the shader resource view
	deviceContext->PSSetSamplers(sampInfo->BindIndex, 1, &samplerState);

	// Success
	return true;
}


bool D3D11Shader::Load(const char * file_name)
{
	unsigned int desc_size = 6;
	D3D11_INPUT_ELEMENT_DESC* input_desc = new D3D11_INPUT_ELEMENT_DESC[desc_size];
	input_desc[0] = { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 };
	input_desc[1] = { "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 };
	input_desc[2] = { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 };
	input_desc[3] = { "TANGENT", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 };
	input_desc[4] = { "BINORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 };
	input_desc[5] = { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 };


	ID3DBlob* error_message = nullptr;

	std::ifstream file;
	file.open(file_name, std::ios_base::binary);

	std::string file_text;
	while (file) {
		std::string s;
		getline(file, s);
		file_text.append(s);
	}
	file.close();

	ID3DBlob* vs_out = nullptr;
	D3DCompile(file_text.data(), file_text.length(), nullptr, nullptr, nullptr, "vs_main", "vs_5_0", 0, 0, &vs_out, &error_message);

	if (error_message)
	{
		OutputDebugStringA((char*)error_message->GetBufferPointer());
		error_message->Release();
		return false;
	}

	D3D11RHI::Device()->CreateVertexShader(vs_out->GetBufferPointer(), vs_out->GetBufferSize(), nullptr, &_VertexShader);
	D3D11RHI::Device()->CreateInputLayout(input_desc, desc_size, vs_out->GetBufferPointer(), vs_out->GetBufferSize(), &_InputLayout);
	vs_out->Release();

	ID3DBlob* ps_out = nullptr;
	D3DCompile(file_text.data(), file_text.length(), nullptr, nullptr, nullptr, "ps_main", "ps_5_0", 0, 0, &ps_out, &error_message);
	if (error_message)
	{
		OutputDebugStringA((char*)error_message->GetBufferPointer());
		error_message->Release();
		return false;
	}

	D3D11RHI::Device()->CreatePixelShader(ps_out->GetBufferPointer(), ps_out->GetBufferSize(), nullptr, &_PixelShader);
	ps_out->Release();

	D3D11_BUFFER_DESC desc;
	memset(&desc, 0, sizeof(decltype(desc)));
	desc.ByteWidth = sizeof(XMMATRIX);
	desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	desc.Usage = D3D11_USAGE_DEFAULT;
	//desc.Usage = D3D11_USAGE_DYNAMIC;
	//desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	D3D11RHI::Device()->CreateBuffer(&desc, nullptr, &_ConstantBuffer);

	return true;
}

void D3D11Shader::Draw(const Matrix& matrix, unsigned int size)
{
	auto wv = XMMatrixMultiply(XMMatrixTranspose(D3D11RHI::Camera()->View()), matrix);
	auto result = XMMatrixMultiply(XMMatrixTranspose(D3D11RHI::Camera()->Perspective()), wv);
	D3D11RHI::Context()->UpdateSubresource(_ConstantBuffer, 0, nullptr, &result, 0, 0);
	D3D11RHI::Context()->VSSetConstantBuffers(0, 1, &_ConstantBuffer);
	D3D11RHI::Context()->IASetInputLayout(_InputLayout);
	D3D11RHI::Context()->VSSetShader(_VertexShader, nullptr, 0);
	D3D11RHI::Context()->PSSetShader(_PixelShader, nullptr, 0);
	D3D11RHI::Context()->DrawIndexed(size, 0, 0);
}
