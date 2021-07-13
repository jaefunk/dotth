


#include "D3D11StaticMesh.h"
#include "ResourceManager.h"

unsigned int D3D11StaticMesh::GetSectionSize(void)
{
	return static_cast<unsigned int>(_VertexBuffers.size());
}

unsigned int D3D11StaticMesh::GetIndicesSize(int index)
{
	D3D11_BUFFER_DESC desc;
	_IndexBuffers[index]->GetDesc(&desc);
	return desc.ByteWidth / sizeof(unsigned int);
}

void D3D11StaticMesh::Load(std::shared_ptr<model> raw)
{
	const auto& sections = raw->sections;
	_VertexBuffers.resize(sections.size());
	_IndexBuffers.resize(sections.size());
	for (auto index = 0; index < sections.size(); ++index)
	{
		D3D11_BUFFER_DESC VertexDesc;
		memset(&VertexDesc, 0, sizeof(decltype(VertexDesc)));
		VertexDesc.Usage = D3D11_USAGE_DEFAULT;
		VertexDesc.ByteWidth = sections[index].GetVerticeByteWidth();
		VertexDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		D3D11_SUBRESOURCE_DATA VertexData;
		memset(&VertexData, 0, sizeof(decltype(VertexData)));
		VertexData.pSysMem = sections[index].vertices.data();
		VertexData.SysMemPitch = 0;
		VertexData.SysMemSlicePitch = 0;
		D3D11RHI::Device()->CreateBuffer(&VertexDesc, &VertexData, &_VertexBuffers[index]);

		D3D11_BUFFER_DESC IndexDesc;
		memset(&IndexDesc, 0, sizeof(decltype(IndexDesc)));
		IndexDesc.Usage = D3D11_USAGE_DEFAULT;
		IndexDesc.ByteWidth = sections[index].GetIndiceByteWidth();
		IndexDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		D3D11_SUBRESOURCE_DATA IndexData;
		memset(&IndexData, 0, sizeof(decltype(IndexData)));
		IndexData.pSysMem = sections[index].indices.data();
		IndexData.SysMemPitch = 0;
		IndexData.SysMemSlicePitch = 0;
		D3D11RHI::Device()->CreateBuffer(&IndexDesc, &IndexData, &_IndexBuffers[index]);
	}
}

void D3D11StaticMesh::Load(const std::string& key)
{
	Load(ResourceManager::Instance()->Find<model>(key));
}

void D3D11StaticMesh::Draw(const unsigned int& index)
{
	const unsigned int offset = 0;
	const unsigned int vertex_type_size = static_cast<unsigned int>(sizeof(vertice));
	D3D11RHI::Context()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	D3D11RHI::Context()->IASetVertexBuffers(0, 1, &_VertexBuffers[index], &vertex_type_size, &offset);
	D3D11RHI::Context()->IASetIndexBuffer(_IndexBuffers[index], DXGI_FORMAT_R32_UINT, 0);
}