
#include "D3D11RHI.h"
#include "Renderable.h"
#include "ResourceManager.h"

Renderable::Renderable(dotth::mesh* raw)
{
	if (raw->positions.size() > 0)
	{
		CreateVertexBuffer(&PositionBuffer, raw->positions.data(), static_cast<unsigned int>(sizeof(dotth::vector3) * raw->positions.size()));
		VertexBuffers.push_back(&PositionBuffer);
		BufferStrides.push_back(sizeof(dotth::vector3));
	}

	if (raw->normals.size() > 0)
	{
		CreateVertexBuffer(&NormalBuffer, raw->normals.data(), static_cast<unsigned int>(sizeof(dotth::vector3) * raw->normals.size()));
		VertexBuffers.push_back(&NormalBuffer);
		BufferStrides.push_back(sizeof(dotth::vector3));
	}

	if (raw->textureCoords.size() > 0)
	{
		CreateVertexBuffer(&TextureCoordBuffer, raw->textureCoords.data(), static_cast<unsigned int>(sizeof(dotth::vector2) * raw->textureCoords.size()));
		VertexBuffers.push_back(&TextureCoordBuffer);
		BufferStrides.push_back(sizeof(dotth::vector2));
	}

	if (raw->boneIds.size() > 0)
	{
		CreateVertexBuffer(&BoneIdBuffer, raw->boneIds.data(), static_cast<unsigned int>(sizeof(dotth::value4<unsigned int>) * raw->boneIds.size()));
		VertexBuffers.push_back(&BoneIdBuffer);
		BufferStrides.push_back(sizeof(dotth::value4<unsigned int>));
	}

	if (raw->weights.size() > 0)
	{
		CreateVertexBuffer(&WeightBuffer, raw->weights.data(), static_cast<unsigned int>(sizeof(dotth::vector4) * raw->boneIds.size()));
		VertexBuffers.push_back(&WeightBuffer);
		BufferStrides.push_back(sizeof(dotth::vector4));
	}

	if (raw->indices.size() > 0)
	{
		CreateIndexBuffer(&IndexBuffer, raw->indices.data(), static_cast<unsigned int>(sizeof(unsigned int) * raw->indices.size()));
		IndexSize = raw->indices.size();
	}
}

void Renderable::Draw(void)
{
	unsigned int offset = 0;
	for (unsigned int i = 0; i < VertexBuffers.size(); ++i)
	{
		D3D11RHI::Context()->IASetVertexBuffers(i, 1, VertexBuffers[i], &BufferStrides[i], &offset);
	}
	D3D11RHI::Context()->IASetIndexBuffer(IndexBuffer, DXGI_FORMAT_R32_UINT, 0);
	D3D11RHI::Context()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	D3D11RHI::Context()->DrawIndexed(IndexSize, 0, 0);
}

void Renderable::CreateVertexBuffer(ID3D11Buffer** buffer, void* data, unsigned int byteWidth)
{
	D3D11_BUFFER_DESC desc;
	memset(&desc, 0, sizeof(decltype(desc)));
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.ByteWidth = byteWidth;
	desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	D3D11_SUBRESOURCE_DATA res;
	memset(&res, 0, sizeof(decltype(res)));
	res.pSysMem = data;
	res.SysMemPitch = 0;
	res.SysMemSlicePitch = 0;
	D3D11RHI::Device()->CreateBuffer(&desc, &res, buffer);
}

void Renderable::CreateIndexBuffer(ID3D11Buffer** buffer, void* data, unsigned int byteWidth)
{
	D3D11_BUFFER_DESC desc;
	memset(&desc, 0, sizeof(decltype(desc)));
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.ByteWidth = byteWidth;
	desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	D3D11_SUBRESOURCE_DATA res;
	memset(&res, 0, sizeof(decltype(res)));
	res.pSysMem = data;
	res.SysMemPitch = 0;
	res.SysMemSlicePitch = 0;
	D3D11RHI::Device()->CreateBuffer(&desc, &res, buffer);
}

