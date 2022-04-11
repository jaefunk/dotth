#pragma once

#include "D3D11.h"

class D3D11Renderable
{
public:
	void AddVertexBuffer(ID3D11Device* pDevice, void* data, unsigned int typeSize, unsigned int count)
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
		pDevice->CreateBuffer(&desc, &res, buffer);
		bufferStrides.push_back(typeSize);
	}

	void SetIndexBuffer(ID3D11Device* pDevice, void* data, unsigned int typeSize, unsigned int count)
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
		pDevice->CreateBuffer(&desc, &res, &indexBuffer);

		indexCount = count;
	}

	void Draw(ID3D11DeviceContext* pContext)
	{
		unsigned int offset = 0;
		for (unsigned int i = 0; i < vertexBuffers.size(); ++i)
		{
			pContext->IASetVertexBuffers(i, 1, vertexBuffers[i], &bufferStrides[i], &offset);
		}
		pContext->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);
		pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		pContext->DrawIndexed(indexCount, 0, 0);
	}

private:
	std::vector<ID3D11Buffer**> vertexBuffers;
	ID3D11Buffer* indexBuffer;
	std::vector<unsigned int> bufferStrides;
	unsigned int indexCount = 0;
};


#include "dotth.h"


class D3D11OrthoRect
{
public:
	struct VertexType
	{
		XMFLOAT3 position;
		XMFLOAT2 texture;
	};

	bool Initialize(ID3D11Device*, int, int);
	void Shutdown();
	void Render(ID3D11DeviceContext* context);
	int GetIndexCount();

private:
	ID3D11Buffer* _VertexBuffer = nullptr;
	ID3D11Buffer* _IndexBuffer = nullptr;
	int _VertexCount = 0;
	int _IndexCount = 0;
};
