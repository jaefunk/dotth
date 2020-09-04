#pragma once

#include "Framework/Asset/Asset_Renderable.h"

#ifdef max
#undef max
#endif
#ifdef min
#undef min
#endif

#include "assimp/Importer.hpp"
#include "assimp/postprocess.h"
#include "assimp/scene.h"

struct VertexPNU
{
	DirectX::XMFLOAT3 p = DirectX::XMFLOAT3(0.f, 0.f, 0.f);
	DirectX::XMFLOAT3 n = DirectX::XMFLOAT3(0.f, 0.f, 0.f);
	DirectX::XMFLOAT2 u = DirectX::XMFLOAT2(0.f, 0.f);
};

struct Mesh
{
	std::vector<VertexPNU> _Vertices;
	std::vector<unsigned long> _Indices;

	bool Init(aiMesh* mesh)
	{
		_Vertices.resize(mesh->mNumVertices);
		for (unsigned int index = 0; index < mesh->mNumVertices; ++index)
		{
			const aiVector3D& p = mesh->mVertices[index];
			_Vertices[index].p.x = p.x;
			_Vertices[index].p.y = p.y;
			_Vertices[index].p.z = p.z;

			const aiVector3D& n = mesh->mNormals[index];
			_Vertices[index].n.x = n.x;
			_Vertices[index].n.y = n.y;
			_Vertices[index].n.z = n.z;

			if (mesh->HasTextureCoords(0))
			{
				const aiVector3D& u = mesh->mTextureCoords[0][index];
				_Vertices[index].u.x = u.x;
				_Vertices[index].u.y = u.y;
			}			
		}

		_Indices.resize(mesh->mNumFaces * 3);
		for (unsigned int index = 0; index < mesh->mNumFaces; ++index)
		{
			const aiFace& face = mesh->mFaces[index];
			_Indices.push_back(face.mIndices[0]);
			_Indices.push_back(face.mIndices[1]);
			_Indices.push_back(face.mIndices[2]);
		}

		return true;
	}
};

class Asset_Model : public Asset_Renderable
{
public:
	Asset_Model(void);
	virtual void Bind(void) override;

private:
	virtual bool OnLoad(void* data, size_t size) override;

public:
	const aiScene* _Scene;
	std::vector<Mesh> _Meshes;
	unsigned int _VertexCount = 0;
	unsigned int _IndexCount = 0;
	std::map<std::string, aiBone*> _Bones;
};