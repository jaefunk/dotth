#pragma once

#include "Shader.h"
#include "D3D11.h"

class D3D11Base
{
public:
	D3D11Base(ID3D11Device* pDevice, ID3D11DeviceContext* pContext) 
		: device(pDevice), context(pContext) {}

protected:
	ID3D11Device* device;
	ID3D11DeviceContext* context;
};

class D3D11Primitive : public D3D11Base
{
public:
	D3D11Primitive(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
		: D3D11Base(pDevice, pContext) {}

	void AddVertexBuffer(void* data, unsigned int typeSize, unsigned int count);
	void SetIndexBuffer(void* data, unsigned int typeSize, unsigned int count);
	void Draw(void);

private:
	std::vector<ID3D11Buffer**> vertexBuffers;
	ID3D11Buffer* indexBuffer = nullptr;
	std::vector<unsigned int> bufferStrides;
	unsigned int indexCount = 0;
};

struct RenderParameter
{
	void* data;
	unsigned int size;
};

class D3D11Shader : public D3D11Base
{
public:
	D3D11Shader(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
		: D3D11Base(pDevice, pContext)
	{
	}

	void LoadVertexShader(const std::string& path)
	{
		vertexShader = new VertexShader(device, context);
		vertexShader->LoadShaderFile(path);
	}

	void LoadPixelShader(const std::string& path)
	{
		pixelShader = new PixelShader(device, context);
		pixelShader->LoadShaderFile(path);
	}

	void Draw(void)
	{
		for (auto& elm : parameters)
		{
			vertexShader->SetData(elm.first, elm.second.data, elm.second.size);
		}
		vertexShader->CopyAllBufferData();
		vertexShader->SetShader();

		for (auto& elm : samplerStates)
		{
			pixelShader->SetSamplerState(elm.first, elm.second);
		}
		for (auto& elm : shaderResourceViews)
		{
			pixelShader->SetShaderResourceView(elm.first, elm.second);
		}
		pixelShader->CopyAllBufferData();
		pixelShader->SetShader();
	}

private:
	// shader
	VertexShader* vertexShader = nullptr;
	PixelShader* pixelShader = nullptr;

	// parameters
	std::unordered_map<std::string, RenderParameter> parameters;
	std::unordered_map<std::string, ID3D11SamplerState*> samplerStates;
	std::unordered_map<std::string, ID3D11ShaderResourceView*> shaderResourceViews;
};

class D3D11Renderable
{
public:
	D3D11Renderable(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	{
		primitive = new D3D11Primitive(pDevice, pContext);
		shader = new D3D11Shader(pDevice, pContext);
	}
	void LoadPrimitive(void)
	{

	}
	void LoadShader(const std::string& path)
	{
		shader->LoadVertexShader(path + "_vs.hlsl");
		shader->LoadPixelShader(path + "_ps.hlsl");
	}

public:
	void Draw(void)
	{
		if (primitive)
			primitive->Draw();
		if (shader)
			shader->Draw();
	}

private:
	D3D11Primitive* primitive = nullptr;
	D3D11Shader* shader = nullptr;
};