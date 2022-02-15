
#include "D3D11RHI.h"
#include "Renderable.h"
#include "ResourceManager.h"

Renderable::Renderable(dotth::mesh* raw)
{
	if (raw->numPositions > 0 && raw->positions != nullptr)
	{
		CreateVertexBuffer(&PositionBuffer, raw->positions, static_cast<unsigned int>(sizeof(dotth::vector3) * raw->numPositions));
		VertexBuffers.push_back(&PositionBuffer);
		BufferStrides.push_back(sizeof(dotth::vector3));
	}

	if (raw->numNormals > 0 && raw->normals != nullptr)
	{
		CreateVertexBuffer(&NormalBuffer, raw->normals, static_cast<unsigned int>(sizeof(dotth::vector3) * raw->numNormals));
		VertexBuffers.push_back(&NormalBuffer);
		BufferStrides.push_back(sizeof(dotth::vector3));
	}

	if (raw->numTextureCoords > 0 && raw->textureCoords != nullptr)
	{
		CreateVertexBuffer(&TextureCoordBuffer, raw->textureCoords, static_cast<unsigned int>(sizeof(dotth::vector2) * raw->numTextureCoords));
		VertexBuffers.push_back(&TextureCoordBuffer);
		BufferStrides.push_back(sizeof(dotth::vector2));
	}

	if (raw->numBones > 0 && raw->bones != nullptr)
	{
		CreateVertexBuffer(&BoneIdBuffer, raw->boneids, static_cast<unsigned int>(sizeof(dotth::uint4) * raw->numBoneIds));
		VertexBuffers.push_back(&BoneIdBuffer);
		BufferStrides.push_back(sizeof(dotth::uint4));

		CreateVertexBuffer(&WeightBuffer, raw->weights, static_cast<unsigned int>(sizeof(dotth::vector4) * raw->numBoneIds));
		VertexBuffers.push_back(&WeightBuffer);
		BufferStrides.push_back(sizeof(dotth::vector4));
	}

	if (raw->numIndices > 0 && raw->indices != nullptr)
	{
		CreateIndexBuffer(&IndexBuffer, raw->indices, static_cast<unsigned int>(sizeof(unsigned int) * raw->numIndices));
		IndexSize = raw->numIndices;
	}

	//printf("%s %d\n", raw->name.c_str(), raw->mateiralIndex);
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

