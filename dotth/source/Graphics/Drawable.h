
#pragma once

#include "Graphics/Renderer.h"

struct VertexPNU
{
	DirectX::XMFLOAT3 p = DirectX::XMFLOAT3(0.f, 0.f, 0.f);
	DirectX::XMFLOAT3 n = DirectX::XMFLOAT3(0.f, 0.f, 0.f);
	DirectX::XMFLOAT2 u = DirectX::XMFLOAT2(0.f, 0.f);
};

class Drawable
{
public:
	ID3D11Buffer* _VertexBuffer = nullptr;
	unsigned int _VertexCount = 0;
	ID3D11Buffer* _IndexBuffer = nullptr;
	unsigned int _IndexCount = 0;

public:
	void SetVertex(const std::vector<VertexPNU>& v)
	{
		_VertexCount = v.size();
		D3D11_BUFFER_DESC desc;
		memset(&desc, 0, sizeof(decltype(desc)));
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.ByteWidth = sizeof(VertexPNU) * v.size();
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		desc.CPUAccessFlags;
		desc.MiscFlags;
		desc.StructureByteStride;
		D3D11_SUBRESOURCE_DATA data;
		data.pSysMem = (void*)v.data();
		data.SysMemPitch = 0;
		data.SysMemSlicePitch = 0;
		_VertexBuffer = Renderer::RHI()->CreateVertexBuffer(desc, data);
	}

	void SetIndex(const std::vector<unsigned int>& v)
	{
		_IndexCount = v.size();
		D3D11_BUFFER_DESC desc;
		memset(&desc, 0, sizeof(decltype(desc)));
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.ByteWidth = sizeof(unsigned int) * v.size();
		desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		desc.CPUAccessFlags;
		desc.MiscFlags;
		desc.StructureByteStride;
		D3D11_SUBRESOURCE_DATA data;
		data.pSysMem = (void*)v.data();
		data.SysMemPitch = 0;
		data.SysMemSlicePitch = 0;
		_IndexBuffer = Renderer::RHI()->CreateIndexBuffer(desc, data);
	}
	
	void Bind(void)
	{
		Renderer::RHI()->BindVertexBuffer(_VertexBuffer, sizeof(VertexPNU), 0);
		Renderer::RHI()->BindIndexBuffer(_IndexBuffer, DXGI_FORMAT_R32_UINT, 0);
	}
};