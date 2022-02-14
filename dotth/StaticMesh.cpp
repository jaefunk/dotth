
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

bool StaticMesh::Load(const std::string& key)
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

unsigned int SkeletalMesh::GetSectionSize(void)
{
	return static_cast<unsigned int>(vertexBuffers.size());
}

unsigned int SkeletalMesh::GetIndicesSize(int index)
{
	D3D11_BUFFER_DESC desc;
	indexBuffers[index]->GetDesc(&desc);
	return desc.ByteWidth / sizeof(unsigned int);
}

bool SkeletalMesh::Load(const std::string& key)
{
	std::shared_ptr<dotth::model> base = ResourceManager2::Find<dotth::model>(key);
	if (base == nullptr)
		return false;


	//vertexBuffers.resize(base->numMeshes);
	//indexBuffers.resize(base->numMeshes);
	//boneIdBuffers.resize(base->numMeshes);
	//

	//unsigned int startID = 0;
	for (auto index = 0; index < base->numMeshes; ++index)
	{
	//	dotth::mesh* pMesh = base->meshes[index];

	//	std::vector<bone> bones;
	//	bones.resize(pMesh->numVertices);
	//	calcBoneList.emplace_back(new XMMATRIX[pMesh->numBones]);
	//	for (auto boneIdx = 0; boneIdx < pMesh->numBones; ++boneIdx)
	//	{
	//		dotth::bone* pBone = pMesh->bones[boneIdx];
	//		calcBoneList.back()[boneIdx] = XMMATRIX(pBone->offset.f);
	//		for (auto weightIdx = 0; weightIdx < pBone->numWeights; ++weightIdx)
	//		{
	//			const dotth::weight& weight = pBone->weights[weightIdx];
	//			auto vertId = weight.vertexID + startID;
	//			auto wei = weight.value;


	//			if (bones[vertId].weight.x == 0) {
	//				bones[vertId].boneID.x = boneIdx;
	//				bones[vertId].weight.x = wei;
	//			}
	//			else if (bones[vertId].weight.y == 0) {
	//				bones[vertId].boneID.y = boneIdx;
	//				bones[vertId].weight.y = wei;
	//			}
	//			else if (bones[vertId].weight.z == 0) {
	//				bones[vertId].boneID.z = boneIdx;
	//				bones[vertId].weight.z = wei;
	//			}
	//			else if (bones[vertId].weight.w == 0) {
	//				bones[vertId].boneID.w = boneIdx;
	//				bones[vertId].weight.w = wei;
	//			}
	//		}
	//	}
	//	startID += pMesh->numVertices;

	//	D3D11_BUFFER_DESC AnimationDesc;
	//	memset(&AnimationDesc, 0, sizeof(decltype(AnimationDesc)));
	//	AnimationDesc.Usage = D3D11_USAGE_DEFAULT;
	//	AnimationDesc.ByteWidth = bones.size() * sizeof(bone);
	//	AnimationDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	//	D3D11_SUBRESOURCE_DATA AnimationData;
	//	memset(&AnimationData, 0, sizeof(decltype(AnimationData)));
	//	AnimationData.pSysMem = bones.data();
	//	AnimationData.SysMemPitch = 0;
	//	AnimationData.SysMemSlicePitch = 0;
	//	D3D11RHI::Device()->CreateBuffer(&AnimationDesc, &AnimationData, &animationBuffers[index]);

	//	

	//	D3D11_BUFFER_DESC VertexDesc;
	//	memset(&VertexDesc, 0, sizeof(decltype(VertexDesc)));
	//	VertexDesc.Usage = D3D11_USAGE_DEFAULT;
	//	VertexDesc.ByteWidth = base->meshes[index]->GetVerticeByteWidth();
	//	VertexDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	//	D3D11_SUBRESOURCE_DATA VertexData;
	//	memset(&VertexData, 0, sizeof(decltype(VertexData)));
	//	VertexData.pSysMem = base->meshes[index]->vertices;
	//	VertexData.SysMemPitch = 0;
	//	VertexData.SysMemSlicePitch = 0;
	//	D3D11RHI::Device()->CreateBuffer(&VertexDesc, &VertexData, &vertexBuffers[index]);

	//	D3D11_BUFFER_DESC IndexDesc;
	//	memset(&IndexDesc, 0, sizeof(decltype(IndexDesc)));
	//	IndexDesc.Usage = D3D11_USAGE_DEFAULT;
	//	IndexDesc.ByteWidth = base->meshes[index]->GetIndiceByteWidth();
	//	IndexDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	//	D3D11_SUBRESOURCE_DATA IndexData;
	//	memset(&IndexData, 0, sizeof(decltype(IndexData)));
	//	IndexData.pSysMem = base->meshes[index]->indices;
	//	IndexData.SysMemPitch = 0;
	//	IndexData.SysMemSlicePitch = 0;
	//	D3D11RHI::Device()->CreateBuffer(&IndexDesc, &IndexData, &indexBuffers[index]);
	}
	return true;
}

void SkeletalMesh::Draw(unsigned int index)
{
	//const unsigned int offset = 0;
	//const unsigned int vertex_type_size = static_cast<unsigned int>(sizeof(dotth::vertice));
	//const unsigned int animation_type_size = static_cast<unsigned int>(sizeof(bone));
	//D3D11RHI::Context()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	//D3D11RHI::Context()->IASetVertexBuffers(0, 1, &vertexBuffers[index], &vertex_type_size, &offset);
	//D3D11RHI::Context()->IASetVertexBuffers(0, 2, &animationBuffers[index], &animation_type_size, &offset);
	//D3D11RHI::Context()->IASetIndexBuffer(indexBuffers[index], DXGI_FORMAT_R32_UINT, 0);
	//D3D11RHI::Context()->DrawIndexed(GetIndicesSize(index), 0, 0);
}

Renderable::Renderable(dotth::mesh* raw)
{
	if (raw->numPositions > 0 && raw->positions != nullptr)
	{
		CreateVertexBuffer(&positionBuffer, raw->positions, static_cast<unsigned int>(sizeof(dotth::vector3) * raw->numPositions));
		VertexBuffers.push_back(&positionBuffer);
		BufferStrides.push_back(sizeof(dotth::vector3));
	}

	if (raw->numNormals > 0 && raw->normals != nullptr)
	{
		CreateVertexBuffer(&normalBuffer, raw->normals, static_cast<unsigned int>(sizeof(dotth::vector3) * raw->numNormals));
		VertexBuffers.push_back(&normalBuffer);
		BufferStrides.push_back(sizeof(dotth::vector3));
	}

	if (raw->numTextureCoords > 0 && raw->textureCoords != nullptr)
	{
		CreateVertexBuffer(&textureCoordBuffer, raw->textureCoords, static_cast<unsigned int>(sizeof(dotth::vector2) * raw->numTextureCoords));
		VertexBuffers.push_back(&textureCoordBuffer);
		BufferStrides.push_back(sizeof(dotth::vector2));
	}

	if (raw->numBones > 0 && raw->bones != nullptr)
	{
		CreateVertexBuffer(&boneIdBuffer, raw->boneids, static_cast<unsigned int>(sizeof(dotth::uint4) * raw->numBoneIds));
		VertexBuffers.push_back(&boneIdBuffer);
		BufferStrides.push_back(sizeof(dotth::uint4));

		CreateVertexBuffer(&weightBuffer, raw->weights, static_cast<unsigned int>(sizeof(dotth::vector4) * raw->numBoneIds));
		VertexBuffers.push_back(&weightBuffer);
		BufferStrides.push_back(sizeof(dotth::vector4));
	}

	if (raw->numIndices > 0 && raw->indices != nullptr)
	{
		CreateIndexBuffer(&indexBuffer, raw->indices, static_cast<unsigned int>(sizeof(unsigned int) * raw->numIndices));
		IndexSize = raw->numIndices;
	}
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

void Renderable::Draw(void)
{
	unsigned int offset = 0;
	for (unsigned int i = 0; i < VertexBuffers.size(); ++i)
	{
		D3D11RHI::Context()->IASetVertexBuffers(i, 1, VertexBuffers[i], &BufferStrides[i], &offset);
	}
	D3D11RHI::Context()->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);
	D3D11RHI::Context()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	D3D11_BUFFER_DESC desc;
	indexBuffer->GetDesc(&desc);
	D3D11RHI::Context()->DrawIndexed(IndexSize, 0, 0);
}

bool StaticMesh2::Load(const std::string& key)
{
	std::shared_ptr<dotth::model> base = ResourceManager2::Find<dotth::model>(key);
	if (base == nullptr)
		return false;

	for (auto index = 0; index < base->numMeshes; ++index)
	{
		Renderables.push_back(new Renderable(base->meshes[index]));
	}
	return true;
}

void StaticMesh2::Draw(unsigned int index)
{
	Renderables[index]->Draw();
}
