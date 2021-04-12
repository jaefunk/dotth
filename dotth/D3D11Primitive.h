#pragma once

#include "dotth.h"
#include "D3D11RHI.h"

struct D3D11MatrixBuffer
{
	XMMATRIX world;
	XMMATRIX view;
	XMMATRIX projection;
};

struct D3D11VertexPNU
{
	XMFLOAT3 p = XMFLOAT3(0.f, 0.f, 0.f);
	XMFLOAT3 n = XMFLOAT3(0.f, 0.f, 0.f);
	XMFLOAT2 u = XMFLOAT2(0.f, 0.f);
};

class D3D11Primitive
{
public:
	ID3D11Buffer* _VertexBuffer = nullptr;
	ID3D11Buffer* _IndexBuffer = nullptr;
	ID3D11Buffer* _ConstantBuffer = nullptr;
	std::size_t _VertexCount = 0;
	std::size_t _IndexCount = 0;

public:
	void SetVertex(const std::vector<D3D11VertexPNU>& v)
	{
		_VertexCount = v.size();
		D3D11_BUFFER_DESC desc;
		memset(&desc, 0, sizeof(decltype(desc)));
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.ByteWidth = static_cast<unsigned int>(sizeof(D3D11VertexPNU) * v.size());
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		desc.CPUAccessFlags;
		desc.MiscFlags;
		desc.StructureByteStride;
		D3D11_SUBRESOURCE_DATA data;
		data.pSysMem = (void*)v.data();
		data.SysMemPitch = 0;
		data.SysMemSlicePitch = 0;
		D3D11RHI::Device()->CreateBuffer(&desc, &data, &_VertexBuffer);
	}

	void SetIndex(const std::vector<unsigned int>& v)
	{
		_IndexCount = v.size();
		D3D11_BUFFER_DESC desc;
		memset(&desc, 0, sizeof(decltype(desc)));
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.ByteWidth = static_cast<unsigned int>(sizeof(unsigned int) * v.size());
		desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		desc.CPUAccessFlags;
		desc.MiscFlags;
		desc.StructureByteStride;
		D3D11_SUBRESOURCE_DATA data;
		data.pSysMem = (void*)v.data();
		data.SysMemPitch = 0;
		data.SysMemSlicePitch = 0;
		D3D11RHI::Device()->CreateBuffer(&desc, &data, &_IndexBuffer);
	}

	void Bind(void)
	{
		const unsigned int stride = sizeof(D3D11VertexPNU);
		const unsigned int offset = 0;
		D3D11RHI::Context()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		D3D11RHI::Context()->IASetVertexBuffers(0, 1, &_VertexBuffer, &stride, &offset);
		D3D11RHI::Context()->IASetIndexBuffer(_IndexBuffer, DXGI_FORMAT_R32_UINT, offset);
	}
};