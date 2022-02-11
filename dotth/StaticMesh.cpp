
#include "StaticMesh.h"
#include "D3D11RHI.h"
#include "ResourceManager.h"

unsigned int StaticMesh::GetSectionSize(void)
{
	return static_cast<unsigned int>(vertexBuffers.size());
}

unsigned int StaticMesh::GetIndicesSize(int index)
{
	D3D11_BUFFER_DESC desc;
	indexBuffers[index]->GetDesc(&desc);
	return desc.ByteWidth / sizeof(unsigned int);
}

bool StaticMesh::Load2(const std::string& key)
{
	std::shared_ptr<dotth::model> base = ResourceManager2::Find<dotth::model>(key);
	if (base == nullptr)
		return false;
	vertexBuffers.resize(base->numMeshes);
	indexBuffers.resize(base->numMeshes);
	for (auto index = 0; index < base->numMeshes; ++index)
	{
		D3D11_BUFFER_DESC VertexDesc;
		memset(&VertexDesc, 0, sizeof(decltype(VertexDesc)));
		VertexDesc.Usage = D3D11_USAGE_DEFAULT;
		VertexDesc.ByteWidth = base->meshes[index]->GetVerticeByteWidth();
		VertexDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		D3D11_SUBRESOURCE_DATA VertexData;
		memset(&VertexData, 0, sizeof(decltype(VertexData)));
		VertexData.pSysMem = base->meshes[index]->vertices;
		VertexData.SysMemPitch = 0;
		VertexData.SysMemSlicePitch = 0;
		D3D11RHI::Device()->CreateBuffer(&VertexDesc, &VertexData, &vertexBuffers[index]);

		D3D11_BUFFER_DESC IndexDesc;
		memset(&IndexDesc, 0, sizeof(decltype(IndexDesc)));
		IndexDesc.Usage = D3D11_USAGE_DEFAULT;
		IndexDesc.ByteWidth = base->meshes[index]->GetIndiceByteWidth();
		IndexDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		D3D11_SUBRESOURCE_DATA IndexData;
		memset(&IndexData, 0, sizeof(decltype(IndexData)));
		IndexData.pSysMem = base->meshes[index]->indices;
		IndexData.SysMemPitch = 0;
		IndexData.SysMemSlicePitch = 0;
		D3D11RHI::Device()->CreateBuffer(&IndexDesc, &IndexData, &indexBuffers[index]);
	}
}

bool StaticMesh::Load(const std::string& key)
{
	std::shared_ptr<Mesh> base = ResourceManager2::Find<Mesh>(key);
	if (base == nullptr)
		return false;
	const auto& primitiveNodes = base->primitiveNodes;
	vertexBuffers.resize(primitiveNodes.size());
	indexBuffers.resize(primitiveNodes.size());
	for (auto index = 0; index < primitiveNodes.size(); ++index)
	{
		D3D11_BUFFER_DESC VertexDesc;
		memset(&VertexDesc, 0, sizeof(decltype(VertexDesc)));
		VertexDesc.Usage = D3D11_USAGE_DEFAULT;
		VertexDesc.ByteWidth = primitiveNodes[index].GetVerticeByteWidth();
		VertexDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		D3D11_SUBRESOURCE_DATA VertexData;
		memset(&VertexData, 0, sizeof(decltype(VertexData)));
		VertexData.pSysMem = primitiveNodes[index].vertices.data();
		VertexData.SysMemPitch = 0;
		VertexData.SysMemSlicePitch = 0;
		D3D11RHI::Device()->CreateBuffer(&VertexDesc, &VertexData, &vertexBuffers[index]);

		D3D11_BUFFER_DESC IndexDesc;
		memset(&IndexDesc, 0, sizeof(decltype(IndexDesc)));
		IndexDesc.Usage = D3D11_USAGE_DEFAULT;
		IndexDesc.ByteWidth = primitiveNodes[index].GetIndiceByteWidth();
		IndexDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		D3D11_SUBRESOURCE_DATA IndexData;
		memset(&IndexData, 0, sizeof(decltype(IndexData)));
		IndexData.pSysMem = primitiveNodes[index].indices.data();
		IndexData.SysMemPitch = 0;
		IndexData.SysMemSlicePitch = 0;
		D3D11RHI::Device()->CreateBuffer(&IndexDesc, &IndexData, &indexBuffers[index]);
	}

	return true;
}

void StaticMesh::Draw(unsigned int index)
{
	const unsigned int offset = 0;
	const unsigned int vertex_type_size = static_cast<unsigned int>(sizeof(dotth::vertice));
	D3D11RHI::Context()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	D3D11RHI::Context()->IASetVertexBuffers(0, 1, &vertexBuffers[index], &vertex_type_size, &offset);
	D3D11RHI::Context()->IASetIndexBuffer(indexBuffers[index], DXGI_FORMAT_R32_UINT, 0);
	D3D11RHI::Context()->DrawIndexed(GetIndicesSize(index), 0, 0);
}
