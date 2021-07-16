#pragma once


#include "Shader.h"
#include "D3D11RHI.h"

// --------------------------------------------------------
// Used by simple shaders to store information about
// specific variables in constant buffers
// --------------------------------------------------------
struct SimpleShaderVariable
{
	unsigned int ByteOffset;
	unsigned int Size;
	unsigned int ConstantBufferIndex;
};

// --------------------------------------------------------
// Contains information about a specific
// constant buffer in a shader, as well as
// the local data buffer for it
// --------------------------------------------------------
struct SimpleConstantBuffer
{
	std::string Name;
	unsigned int Size;
	unsigned int BindIndex;
	ID3D11Buffer* ConstantBuffer;
	unsigned char* LocalDataBuffer;
	std::vector<SimpleShaderVariable> Variables;
};

// --------------------------------------------------------
// Contains info about a single SRV in a shader
// --------------------------------------------------------
struct SimpleSRV
{
	unsigned int Index;		// The raw index of the SRV
	unsigned int BindIndex; // The register of the SRV
};

// --------------------------------------------------------
// Contains info about a single Sampler in a shader
// --------------------------------------------------------
struct SimpleSampler
{
	unsigned int Index;		// The raw index of the Sampler
	unsigned int BindIndex; // The register of the Sampler
};

// --------------------------------------------------------
// Base abstract class for simplifying shader handling
// --------------------------------------------------------
class ISimpleShader
{
public:
	ISimpleShader(ID3D11Device* device, ID3D11DeviceContext* context);
	virtual ~ISimpleShader();

	// Initialization method (since we can't invoke derived class
	// overrides in the base class constructor)
	bool LoadShaderFile(LPCWSTR shaderFile);

	// Simple helpers
	bool IsShaderValid() { return shaderValid; }

	// Activating the shader and copying data
	void SetShader();
	void CopyAllBufferData();
	void CopyBufferData(unsigned int index);
	void CopyBufferData(std::string bufferName);

	// Sets arbitrary shader data
	bool SetData(std::string name, const void* data, unsigned int size);

	bool SetInt(std::string name, int data);
	bool SetFloat(std::string name, float data);
	bool SetFloat2(std::string name, const float data[2]);
	bool SetFloat2(std::string name, const DirectX::XMFLOAT2 data);
	bool SetFloat3(std::string name, const float data[3]);
	bool SetFloat3(std::string name, const DirectX::XMFLOAT3 data);
	bool SetFloat4(std::string name, const float data[4]);
	bool SetFloat4(std::string name, const DirectX::XMFLOAT4 data);
	bool SetMatrix4x4(std::string name, const float data[16]);
	bool SetMatrix4x4(std::string name, const DirectX::XMFLOAT4X4 data);

	// Setting shader resources
	virtual bool SetShaderResourceView(std::string name, ID3D11ShaderResourceView* srv) = 0;
	virtual bool SetSamplerState(std::string name, ID3D11SamplerState* samplerState) = 0;

	// Getting data about variables and resources
	const SimpleShaderVariable* GetVariableInfo(std::string name);

	const SimpleSRV* GetShaderResourceViewInfo(std::string name);
	const SimpleSRV* GetShaderResourceViewInfo(unsigned int index);
	unsigned int GetShaderResourceViewCount() { return static_cast<unsigned int>(textureTable.size()); }

	const SimpleSampler* GetSamplerInfo(std::string name);
	const SimpleSampler* GetSamplerInfo(unsigned int index);
	unsigned int GetSamplerCount() { return static_cast<unsigned int>(samplerTable.size()); }

	// Get data about constant buffers
	unsigned int GetBufferCount();
	unsigned int GetBufferSize(unsigned int index);
	const SimpleConstantBuffer* GetBufferInfo(std::string name);
	const SimpleConstantBuffer* GetBufferInfo(unsigned int index);

	// Misc getters
	ID3DBlob* GetShaderBlob() { return shaderBlob; }

protected:

	bool shaderValid;
	ID3DBlob* shaderBlob;
	ID3D11Device* device;
	ID3D11DeviceContext* deviceContext;

	// Resource counts
	unsigned int constantBufferCount;

	// Maps for variables and buffers
	SimpleConstantBuffer* constantBuffers; // For index-based lookup
	std::vector<SimpleSRV*>		shaderResourceViews;
	std::vector<SimpleSampler*>	samplerStates;
	std::unordered_map<std::string, SimpleConstantBuffer*> cbTable;
	std::unordered_map<std::string, SimpleShaderVariable> varTable;
	std::unordered_map<std::string, SimpleSRV*> textureTable;
	std::unordered_map<std::string, SimpleSampler*> samplerTable;

	// Pure virtual functions for dealing with shader types
	virtual bool CreateShader(ID3DBlob* shaderBlob) = 0;
	virtual void SetShaderAndCBs() = 0;

	virtual void CleanUp();

	// Helpers for finding data by name
	SimpleShaderVariable* FindVariable(std::string name, int size);
	SimpleConstantBuffer* FindConstantBuffer(std::string name);
};

// --------------------------------------------------------
// Derived class for VERTEX shaders ///////////////////////
// --------------------------------------------------------
class SimpleVertexShader : public ISimpleShader
{
public:
	SimpleVertexShader(ID3D11Device* device, ID3D11DeviceContext* context);
	SimpleVertexShader(ID3D11Device* device, ID3D11DeviceContext* context, ID3D11InputLayout* inputLayout, bool perInstanceCompatible);
	~SimpleVertexShader();
	ID3D11VertexShader* GetDirectXShader() { return shader; }
	ID3D11InputLayout* GetInputLayout() { return inputLayout; }
	bool GetPerInstanceCompatible() { return perInstanceCompatible; }

	bool SetShaderResourceView(std::string name, ID3D11ShaderResourceView* srv);
	bool SetSamplerState(std::string name, ID3D11SamplerState* samplerState);

protected:
	bool perInstanceCompatible;
	ID3D11InputLayout* inputLayout;
	ID3D11VertexShader* shader;
	bool CreateShader(ID3DBlob* shaderBlob);
	void SetShaderAndCBs();
	void CleanUp();
};


// --------------------------------------------------------
// Derived class for PIXEL shaders ////////////////////////
// --------------------------------------------------------
class SimplePixelShader : public ISimpleShader
{
public:
	SimplePixelShader(ID3D11Device* device, ID3D11DeviceContext* context);
	~SimplePixelShader();
	ID3D11PixelShader* GetDirectXShader() { return shader; }

	bool SetShaderResourceView(std::string name, ID3D11ShaderResourceView* srv);
	bool SetSamplerState(std::string name, ID3D11SamplerState* samplerState);

protected:
	ID3D11PixelShader* shader;
	bool CreateShader(ID3DBlob* shaderBlob);
	void SetShaderAndCBs();
	void CleanUp();
};

class D3D11Shader : public Shader
{
private:
	ID3D11Buffer* _ConstantBuffer = nullptr;
	ID3D11VertexShader* _VertexShader = nullptr;
	ID3D11PixelShader* _PixelShader = nullptr;
	ID3D11InputLayout* _InputLayout = nullptr;


	ID3D11ShaderResourceView* _SRV = nullptr;

public:
	virtual bool Load(const char* FileName) override;
	virtual void Draw(const Matrix& matrix, unsigned int size) override;
};
