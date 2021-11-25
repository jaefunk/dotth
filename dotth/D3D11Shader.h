#pragma once

#include "D3D11RHI.h"

struct ShaderVariable
{
	unsigned int ByteOffset;
	unsigned int Size;
	unsigned int ConstantBufferIndex;
};

struct ConstantBuffer
{
	std::string Name;
	unsigned int Size;
	unsigned int BindIndex;
	ID3D11Buffer* ConstantBuffer;
	unsigned char* LocalDataBuffer;
	std::vector<ShaderVariable> Variables;
};

struct ShaderResourceView
{
	unsigned int Index;		
	unsigned int BindIndex;
};

struct Sampler
{
	unsigned int Index;		
	unsigned int BindIndex; 
};

class IShader
{
public:
	IShader(ID3D11Device* device, ID3D11DeviceContext* context);
	virtual ~IShader(void);

	// Initialization method (since we can't invoke derived class
	// overrides in the base class constructor)
	bool LoadShaderFile(LPCWSTR shaderFile);

	// Simple helpers
	bool IsShaderValid(void) { return shaderValid; }

	// Activating the shader and copying data
	void SetShader(void);
	void CopyAllBufferData(void);
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
	const ShaderVariable* GetVariableInfo(std::string name);

	const ShaderResourceView* GetShaderResourceViewInfo(std::string name);
	const ShaderResourceView* GetShaderResourceViewInfo(unsigned int index);
	unsigned int GetShaderResourceViewCount(void) { return static_cast<unsigned int>(textureTable.size()); }

	const Sampler* GetSamplerInfo(std::string name);
	const Sampler* GetSamplerInfo(unsigned int index);
	unsigned int GetSamplerCount(void) { return static_cast<unsigned int>(samplerTable.size()); }

	// Get data about constant buffers
	unsigned int GetBufferCount(void);
	unsigned int GetBufferSize(unsigned int index);
	const ConstantBuffer* GetBufferInfo(std::string name);
	const ConstantBuffer* GetBufferInfo(unsigned int index);

	// Misc getters
	ID3DBlob* GetShaderBlob() { return shaderBlob; }

protected:

	bool shaderValid;
	ID3DBlob* shaderBlob;
	ID3D11Device* device;
	ID3D11DeviceContext* deviceContext;

	// Resource counts
	unsigned int constantBufferCount;

	ConstantBuffer* constantBuffers;
	std::vector<ShaderResourceView*> shaderResourceViews;
	std::vector<Sampler*> samplerStates;
	std::unordered_map<std::string, ConstantBuffer*> cbTable;
	std::unordered_map<std::string, ShaderVariable> varTable;
	std::unordered_map<std::string, ShaderResourceView*> textureTable;
	std::unordered_map<std::string, Sampler*> samplerTable;

	virtual bool CreateShader(ID3DBlob* shaderBlob) = 0;
	virtual void SetShaderAndConstantsBuffers() = 0;

	virtual void CleanUp(void);

	ShaderVariable* FindVariable(std::string name, int size);
	ConstantBuffer* FindConstantBuffer(std::string name);
};

class VertexShader : public IShader
{
public:
	VertexShader(ID3D11Device* device, ID3D11DeviceContext* context);
	VertexShader(ID3D11Device* device, ID3D11DeviceContext* context, ID3D11InputLayout* inputLayout, bool perInstanceCompatible);
	virtual ~VertexShader(void);
	ID3D11VertexShader* GetShader(void);
	ID3D11InputLayout* GetInputLayout(void);
	bool GetPerInstanceCompatible(void);

	bool SetShaderResourceView(std::string name, ID3D11ShaderResourceView* srv);
	bool SetSamplerState(std::string name, ID3D11SamplerState* samplerState);

protected:
	bool perInstanceCompatible;
	ID3D11InputLayout* inputLayout;
	ID3D11VertexShader* shader;
	bool CreateShader(ID3DBlob* shaderBlob);
	void SetShaderAndConstantsBuffers(void);
	void CleanUp(void);
};

class PixelShader : public IShader
{
public:
	PixelShader(ID3D11Device* device, ID3D11DeviceContext* context);
	virtual ~PixelShader(void);
	ID3D11PixelShader* GetShader(void);

	bool SetShaderResourceView(std::string name, ID3D11ShaderResourceView* srv);
	bool SetSamplerState(std::string name, ID3D11SamplerState* samplerState);

protected:
	ID3D11PixelShader* shader;
	bool CreateShader(ID3DBlob* shaderBlob);
	void SetShaderAndConstantsBuffers(void);
	void CleanUp(void);
};