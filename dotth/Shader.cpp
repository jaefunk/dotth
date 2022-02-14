
#include "Shader.h"

IShader::IShader(ID3D11Device* device, ID3D11DeviceContext* context)
{
	this->device = device;
	this->deviceContext = context;

	constantBufferCount = 0;
	constantBuffers = 0;
	shaderBlob = 0;
}

IShader::~IShader()
{
	if (shaderBlob)
		shaderBlob->Release();
}

void IShader::CleanUp()
{
	for (unsigned int i = 0; i < constantBufferCount; i++)
	{
		constantBuffers[i].buffer->Release();
		delete[] constantBuffers[i].localDataBuffer;
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

	varTable.clear();
	cbTable.clear();
	samplerTable.clear();
	textureTable.clear();
}

bool IShader::LoadShaderFile(LPCWSTR shaderFile)
{
	HRESULT hr = D3DReadFileToBlob(shaderFile, &shaderBlob);
	if (hr != S_OK)
	{
		return false;
	}

	shaderValid = CreateShader(shaderBlob);
	if (!shaderValid)
	{
		return false;
	}

	ID3D11ShaderReflection* refl;
	D3DReflect(
		shaderBlob->GetBufferPointer(),
		shaderBlob->GetBufferSize(),
		IID_ID3D11ShaderReflection,
		(void**)&refl);

	D3D11_SHADER_DESC shaderDesc;
	refl->GetDesc(&shaderDesc);

	constantBufferCount = shaderDesc.ConstantBuffers;
	constantBuffers = new ConstantBuffer[constantBufferCount];

	unsigned int resourceCount = shaderDesc.BoundResources;
	for (unsigned int r = 0; r < resourceCount; r++)
	{
		D3D11_SHADER_INPUT_BIND_DESC resourceDesc;
		refl->GetResourceBindingDesc(r, &resourceDesc);

		switch (resourceDesc.Type)
		{
		case D3D_SIT_TEXTURE:
		{
			ShaderResourceView* srv = new ShaderResourceView();
			srv->bindIndex = resourceDesc.BindPoint;
			srv->index = static_cast<unsigned int>(shaderResourceViews.size());
			textureTable.insert(std::pair<std::string, ShaderResourceView*>(resourceDesc.Name, srv));
			shaderResourceViews.push_back(srv);
		}
		break;

		case D3D_SIT_SAMPLER:
		{
			Sampler* sampler = new Sampler();
			sampler->bindIndex = resourceDesc.BindPoint;
			sampler->index = static_cast<unsigned int>(samplerStates.size());
			samplerTable.insert(std::pair<std::string, Sampler*>(resourceDesc.Name, sampler));
			samplerStates.push_back(sampler);
		}
		break;
		}
	}

	for (unsigned int b = 0; b < constantBufferCount; b++)
	{
		ID3D11ShaderReflectionConstantBuffer* cb = refl->GetConstantBufferByIndex(b);

		D3D11_SHADER_BUFFER_DESC bufferDesc;
		cb->GetDesc(&bufferDesc);

		D3D11_SHADER_INPUT_BIND_DESC bindDesc;
		refl->GetResourceBindingDescByName(bufferDesc.Name, &bindDesc);

		constantBuffers[b].bindIndex = bindDesc.BindPoint;
		constantBuffers[b].name = bufferDesc.Name;
		cbTable.insert(std::pair<std::string, ConstantBuffer*>(bufferDesc.Name, &constantBuffers[b]));

		D3D11_BUFFER_DESC newBuffDesc;
		newBuffDesc.Usage = D3D11_USAGE_DEFAULT;
		newBuffDesc.ByteWidth = bufferDesc.Size;
		newBuffDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		newBuffDesc.CPUAccessFlags = 0;
		newBuffDesc.MiscFlags = 0;
		newBuffDesc.StructureByteStride = 0;
		device->CreateBuffer(&newBuffDesc, 0, &constantBuffers[b].buffer);

		constantBuffers[b].size = bufferDesc.Size;
		constantBuffers[b].localDataBuffer = new unsigned char[bufferDesc.Size];
		ZeroMemory(constantBuffers[b].localDataBuffer, bufferDesc.Size);

		for (unsigned int v = 0; v < bufferDesc.Variables; v++)
		{
			ID3D11ShaderReflectionVariable* var = cb->GetVariableByIndex(v);

			D3D11_SHADER_VARIABLE_DESC varDesc;
			var->GetDesc(&varDesc);

			ShaderVariable varStruct;
			varStruct.constantBufferIndex = b;
			varStruct.byteOffset = varDesc.StartOffset;
			varStruct.size = varDesc.Size;

			std::string varName(varDesc.Name);

			varTable.insert(std::pair<std::string, ShaderVariable>(varName, varStruct));
			constantBuffers[b].variables.push_back(varStruct);
		}
	}

	refl->Release();
	return true;
}

bool IShader::IsShaderValid(void) 
{
	return shaderValid; 
}

ShaderVariable* IShader::FindVariable(std::string name, int size)
{
	std::unordered_map<std::string, ShaderVariable>::iterator result = varTable.find(name);

	if (result == varTable.end())
		return 0;

	ShaderVariable* var = &(result->second);

	if (size > 0 && var->size != size)
		return 0;

	return var;
}

ConstantBuffer* IShader::FindConstantBuffer(std::string name)
{
	std::unordered_map<std::string, ConstantBuffer*>::iterator result =
		cbTable.find(name);

	if (result == cbTable.end())
		return 0;

	return result->second;
}

void IShader::SetShader()
{
	if (!shaderValid) 
		return;

	SetShaderAndConstantsBuffers();
}

void IShader::CopyAllBufferData()
{
	if (!shaderValid) 
		return;

	for (unsigned int i = 0; i < constantBufferCount; i++)
	{
		deviceContext->UpdateSubresource(constantBuffers[i].buffer, 0, 0, constantBuffers[i].localDataBuffer, 0, 0);
	}
}

void IShader::CopyBufferData(unsigned int index)
{
	if (!shaderValid) 
		return;

	if (index >= this->constantBufferCount)
		return;

	ConstantBuffer* cb = &this->constantBuffers[index];
	if (!cb)
		return;

	deviceContext->UpdateSubresource(cb->buffer, 0, 0, cb->localDataBuffer, 0, 0);
}

void IShader::CopyBufferData(std::string bufferName)
{
	if (!shaderValid) 
		return;

	ConstantBuffer* cb = this->FindConstantBuffer(bufferName);
	if (!cb) 
		return;

	deviceContext->UpdateSubresource(cb->buffer, 0, 0, cb->localDataBuffer, 0, 0);
}


bool IShader::SetData(std::string name, const void* data, unsigned int size)
{
	ShaderVariable* var = FindVariable(name, size);
	if (var == 0)
		return false;

	memcpy(constantBuffers[var->constantBufferIndex].localDataBuffer + var->byteOffset, data, size);

	return true;
}

bool IShader::SetInt(std::string name, int data)
{
	return this->SetData(name, (void*)(&data), sizeof(int));
}

bool IShader::SetFloat(std::string name, float data)
{
	return this->SetData(name, (void*)(&data), sizeof(float));
}

bool IShader::SetFloat2(std::string name, const float data[2])
{
	return this->SetData(name, (void*)data, sizeof(float) * 2);
}

bool IShader::SetFloat2(std::string name, const DirectX::XMFLOAT2 data)
{
	return this->SetData(name, &data, sizeof(float) * 2);
}

bool IShader::SetFloat3(std::string name, const float data[3])
{
	return this->SetData(name, (void*)data, sizeof(float) * 3);
}

bool IShader::SetFloat3(std::string name, const DirectX::XMFLOAT3 data)
{
	return this->SetData(name, &data, sizeof(float) * 3);
}

bool IShader::SetFloat4(std::string name, const float data[4])
{
	return this->SetData(name, (void*)data, sizeof(float) * 4);
}

bool IShader::SetFloat4(std::string name, const DirectX::XMFLOAT4 data)
{
	return this->SetData(name, &data, sizeof(float) * 4);
}

bool IShader::SetMatrix4x4(std::string name, const float data[16])
{
	return this->SetData(name, (void*)data, sizeof(float) * 16);
}

bool IShader::SetMatrix4x4(std::string name, const DirectX::XMFLOAT4X4 data)
{
	return this->SetData(name, &data, sizeof(float) * 16);
}

const ShaderVariable* IShader::GetVariableInfo(std::string name)
{
	return FindVariable(name, -1);
}

const ShaderResourceView* IShader::GetShaderResourceViewInfo(std::string name)
{
	std::unordered_map<std::string, ShaderResourceView*>::iterator result = textureTable.find(name);

	if (result == textureTable.end())
		return 0;

	return result->second;
}

const ShaderResourceView* IShader::GetShaderResourceViewInfo(unsigned int index)
{
	if (index >= shaderResourceViews.size()) 
		return 0;

	return shaderResourceViews[index];
}

const Sampler* IShader::GetSamplerInfo(std::string name)
{
	std::unordered_map<std::string, Sampler*>::iterator result = samplerTable.find(name);

	if (result == samplerTable.end())
		return 0;

	return result->second;
}

const Sampler* IShader::GetSamplerInfo(unsigned int index)
{
	if (index >= samplerStates.size()) 
		return 0;

	return samplerStates[index];
}

unsigned int IShader::GetBufferCount() 
{
	return constantBufferCount; 
}

unsigned int IShader::GetBufferSize(unsigned int index)
{
	if (index >= constantBufferCount)
		return -1;

	return constantBuffers[index].size;
}

const ConstantBuffer* IShader::GetBufferInfo(std::string name)
{
	return FindConstantBuffer(name);
}

const ConstantBuffer* IShader::GetBufferInfo(unsigned int index)
{
	if (index >= constantBufferCount) 
		return 0;

	return &constantBuffers[index];
}

VertexShader::VertexShader(ID3D11Device* device, ID3D11DeviceContext* context)
	: IShader(device, context)
{
	this->inputLayout = nullptr;
	this->shader = nullptr;
	this->perInstanceCompatible = false;
}

VertexShader::VertexShader(ID3D11Device* device, ID3D11DeviceContext* context, ID3D11InputLayout* inputLayout, bool perInstanceCompatible)
	: IShader(device, context)
{
	this->inputLayout = inputLayout;
	this->shader = nullptr;
	this->perInstanceCompatible = perInstanceCompatible;
}

VertexShader::~VertexShader(void)
{
	CleanUp();
}

ID3D11VertexShader* VertexShader::GetShader(void)
{
	return shader;
}

ID3D11InputLayout* VertexShader::GetInputLayout(void)
{
	return inputLayout;
}

bool VertexShader::GetPerInstanceCompatible(void)
{
	return perInstanceCompatible;
}

void VertexShader::CleanUp(void)
{
	IShader::CleanUp();
	if (shader) 
	{
		shader->Release(); 
		shader = nullptr; 
	}
	if (inputLayout) 
	{
		inputLayout->Release(); 
		inputLayout = nullptr; 
	}
}

bool VertexShader::CreateShader(ID3DBlob* shaderBlob)
{
	this->CleanUp();

	HRESULT result = device->CreateVertexShader(shaderBlob->GetBufferPointer(), shaderBlob->GetBufferSize(), 0, &shader);

	if (result != S_OK)
		return false;

	if (inputLayout)
		return true;

	ID3D11ShaderReflection* refl;
	D3DReflect(shaderBlob->GetBufferPointer(), shaderBlob->GetBufferSize(), IID_ID3D11ShaderReflection, (void**)&refl);

	D3D11_SHADER_DESC shaderDesc;
	refl->GetDesc(&shaderDesc);

	std::vector<D3D11_INPUT_ELEMENT_DESC> inputLayoutDesc;
	for (unsigned int i = 0; i < shaderDesc.InputParameters; i++)
	{
		D3D11_SIGNATURE_PARAMETER_DESC paramDesc;
		refl->GetInputParameterDesc(i, &paramDesc);

		std::string perInstanceStr = "_PER_INSTANCE";
		std::string sem = paramDesc.SemanticName;
		int lenDiff = static_cast<int>(sem.size() - perInstanceStr.size());
		bool isPerInstance = lenDiff >= 0 && sem.compare(lenDiff, perInstanceStr.size(), perInstanceStr) == 0;

		D3D11_INPUT_ELEMENT_DESC elementDesc;
		elementDesc.SemanticName = paramDesc.SemanticName;
		elementDesc.SemanticIndex = 0;
		elementDesc.InputSlot = i;
		elementDesc.AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
		elementDesc.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		elementDesc.InstanceDataStepRate = 0;

		if (isPerInstance)
		{
			elementDesc.InputSlot = 1;
			elementDesc.InputSlotClass = D3D11_INPUT_PER_INSTANCE_DATA;
			elementDesc.InstanceDataStepRate = 1;

			perInstanceCompatible = true;
		}

		if (paramDesc.Mask == 1)
		{
			if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32) 
				elementDesc.Format = DXGI_FORMAT_R32_UINT;
			else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32) 
				elementDesc.Format = DXGI_FORMAT_R32_SINT;
			else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32) 
				elementDesc.Format = DXGI_FORMAT_R32_FLOAT;
		}
		else if (paramDesc.Mask <= 3)
		{
			if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32) 
				elementDesc.Format = DXGI_FORMAT_R32G32_UINT;
			else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32) 
				elementDesc.Format = DXGI_FORMAT_R32G32_SINT;
			else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32) 
				elementDesc.Format = DXGI_FORMAT_R32G32_FLOAT;
		}
		else if (paramDesc.Mask <= 7)
		{
			if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32) 
				elementDesc.Format = DXGI_FORMAT_R32G32B32_UINT;
			else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32) 
				elementDesc.Format = DXGI_FORMAT_R32G32B32_SINT;
			else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32) 
				elementDesc.Format = DXGI_FORMAT_R32G32B32_FLOAT;
		}
		else if (paramDesc.Mask <= 15)
		{
			if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32) 
				elementDesc.Format = DXGI_FORMAT_R32G32B32A32_UINT;
			else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32) 
				elementDesc.Format = DXGI_FORMAT_R32G32B32A32_SINT;
			else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32) 
				elementDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		}

		inputLayoutDesc.push_back(elementDesc);
	}

	HRESULT hr = device->CreateInputLayout(&inputLayoutDesc[0], static_cast<unsigned int>(inputLayoutDesc.size()), shaderBlob->GetBufferPointer(), shaderBlob->GetBufferSize(), &inputLayout);

	refl->Release();
	return true;
}

void VertexShader::SetShaderAndConstantsBuffers(void)
{
	if (!shaderValid) 
		return;

	deviceContext->IASetInputLayout(inputLayout);
	deviceContext->VSSetShader(shader, 0, 0);

	for (unsigned int i = 0; i < constantBufferCount; i++)
	{
		deviceContext->VSSetConstantBuffers(constantBuffers[i].bindIndex, 1, &constantBuffers[i].buffer);
	}
}

bool VertexShader::SetShaderResourceView(std::string name, ID3D11ShaderResourceView* srv)
{
	const ShaderResourceView* srvInfo = GetShaderResourceViewInfo(name);
	if (srvInfo == 0)
		return false;

	deviceContext->VSSetShaderResources(srvInfo->bindIndex, 1, &srv);
	return true;
}

bool VertexShader::SetSamplerState(std::string name, ID3D11SamplerState* samplerState)
{
	const Sampler* sampInfo = GetSamplerInfo(name);
	if (sampInfo == 0)
		return false;

	deviceContext->VSSetSamplers(sampInfo->bindIndex, 1, &samplerState);

	return true;
}

PixelShader::PixelShader(ID3D11Device* device, ID3D11DeviceContext* context)
	: IShader(device, context)
{
	this->shader = nullptr;
}

PixelShader::~PixelShader(void)
{
	CleanUp();
}

ID3D11PixelShader* PixelShader::GetShader(void)
{
	return shader; 
}

void PixelShader::CleanUp(void)
{
	IShader::CleanUp();
	if (shader) 
	{ 
		shader->Release(); 
		shader = 0; 
	}
}

bool PixelShader::CreateShader(ID3DBlob* shaderBlob)
{
	this->CleanUp();
	HRESULT result = device->CreatePixelShader(shaderBlob->GetBufferPointer(), shaderBlob->GetBufferSize(), 0, &shader);
	return result == S_OK;
}

void PixelShader::SetShaderAndConstantsBuffers(void)
{
	if (!shaderValid) 
		return;

	deviceContext->PSSetShader(shader, 0, 0);

	for (unsigned int i = 0; i < constantBufferCount; i++)
	{
		deviceContext->PSSetConstantBuffers(constantBuffers[i].bindIndex, 1, &constantBuffers[i].buffer);
	}
}

bool PixelShader::SetShaderResourceView(std::string name, ID3D11ShaderResourceView* srv)
{
	const ShaderResourceView* srvInfo = GetShaderResourceViewInfo(name);
	if (srvInfo == 0)
		return false;

	deviceContext->PSSetShaderResources(srvInfo->bindIndex, 1, &srv);

	return true;
}

bool PixelShader::SetSamplerState(std::string name, ID3D11SamplerState* samplerState)
{
	const Sampler* sampInfo = GetSamplerInfo(name);
	if (sampInfo == 0)
		return false;

	deviceContext->PSSetSamplers(sampInfo->bindIndex, 1, &samplerState);

	return true;
}


