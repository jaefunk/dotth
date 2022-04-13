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

class D3D11Renderable : public D3D11Base
{
public:
	D3D11Renderable(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
		: D3D11Base(pDevice, pContext) {}

public:
	void AddVertexBuffer(void* data, unsigned int typeSize, unsigned int count)
	{
		vertexBuffers.emplace_back();
		ID3D11Buffer** buffer = vertexBuffers.back();
		D3D11_BUFFER_DESC desc;
		memset(&desc, 0, sizeof(decltype(desc)));
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.ByteWidth = typeSize * count;
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		D3D11_SUBRESOURCE_DATA res;
		memset(&res, 0, sizeof(decltype(res)));
		res.pSysMem = data;
		res.SysMemPitch = 0;
		res.SysMemSlicePitch = 0;
		device->CreateBuffer(&desc, &res, buffer);
		bufferStrides.push_back(typeSize);
	}

	void SetIndexBuffer(void* data, unsigned int typeSize, unsigned int count)
	{
		D3D11_BUFFER_DESC desc;
		memset(&desc, 0, sizeof(decltype(desc)));
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.ByteWidth = typeSize * count;
		desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		D3D11_SUBRESOURCE_DATA res;
		memset(&res, 0, sizeof(decltype(res)));
		res.pSysMem = data;
		res.SysMemPitch = 0;
		res.SysMemSlicePitch = 0;
		device->CreateBuffer(&desc, &res, &indexBuffer);

		indexCount = count;
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
		unsigned int offset = 0;
		for (unsigned int i = 0; i < vertexBuffers.size(); ++i)
		{
			context->IASetVertexBuffers(i, 1, vertexBuffers[i], &bufferStrides[i], &offset);
		}
		context->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);
		context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		context->DrawIndexed(indexCount, 0, 0);

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
	std::vector<ID3D11Buffer**> vertexBuffers;
	ID3D11Buffer* indexBuffer = nullptr;
	std::vector<unsigned int> bufferStrides;
	unsigned int indexCount = 0;

private:
	// shader
	VertexShader* vertexShader = nullptr;
	PixelShader* pixelShader = nullptr;

	// parameters
	std::unordered_map<std::string, RenderParameter> parameters;
	std::unordered_map<std::string, ID3D11SamplerState*> samplerStates;
	std::unordered_map<std::string, ID3D11ShaderResourceView*> shaderResourceViews;
};