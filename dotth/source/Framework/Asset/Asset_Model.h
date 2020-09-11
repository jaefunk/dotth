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

#include "Graphics/Drawable.h"

struct Mesh
{
	std::vector<VertexPNU> _Vertices;
	std::vector<unsigned long> _Indices;

	Mesh(aiMesh* mesh)
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

			const aiVector3D& t = mesh->mTangents[index];

			const aiVector3D& b = mesh->mBitangents[index];

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
	std::vector<Drawable> _Drawables;
};