#include "Asset3D.h"
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

std::unique_ptr<Mesh> FBXLoader::Load(const std::string& filePath)
{
	std::unique_ptr<Mesh> mesh = std::make_unique<Mesh>();
	Assimp::Importer importer;
	unsigned int flags = aiProcess_ConvertToLeftHanded | aiProcess_Triangulate | aiProcess_OptimizeMeshes;
	auto scene = importer.ReadFile(filePath, flags);
	if (scene == nullptr)
		return mesh;
	mesh->primitiveNodes.resize(scene->mNumMeshes);
	for (unsigned int index = 0; index < scene->mNumMeshes; ++index)
	{
		auto sceneMesh = scene->mMeshes[index];
		PrimitiveNode& node = mesh->primitiveNodes[index];
		node.vertices.resize(sceneMesh->mNumVertices);
		for (unsigned int i = 0; i < sceneMesh->mNumVertices; ++i)
		{
			if (sceneMesh->HasPositions())
			{
				node.vertices[i].position.x = sceneMesh->mVertices[i].x;
				node.vertices[i].position.y = -sceneMesh->mVertices[i].z;
				node.vertices[i].position.z = sceneMesh->mVertices[i].y;
			}

			if (sceneMesh->HasNormals())
			{
				node.vertices[i].normal.x = sceneMesh->mNormals[i].x;
				node.vertices[i].normal.y = -sceneMesh->mNormals[i].z;
				node.vertices[i].normal.z = sceneMesh->mNormals[i].y;
			}

			if (sceneMesh->HasTangentsAndBitangents())
			{
				node.vertices[i].tangent.x = sceneMesh->mTangents[i].x;
				node.vertices[i].tangent.y = sceneMesh->mTangents[i].y;
				node.vertices[i].tangent.z = sceneMesh->mTangents[i].z;
			}

			if (sceneMesh->HasTangentsAndBitangents())
			{
				node.vertices[i].bitangent.x = sceneMesh->mBitangents[i].x;
				node.vertices[i].bitangent.y = sceneMesh->mBitangents[i].y;
				node.vertices[i].bitangent.z = sceneMesh->mBitangents[i].z;
			}

			if (sceneMesh->HasTextureCoords(0))
			{
				node.vertices[i].textureCoord.x = sceneMesh->mTextureCoords[0][i].x;
				node.vertices[i].textureCoord.y = sceneMesh->mTextureCoords[0][i].y;
			}

			if (sceneMesh->HasVertexColors(0))
			{
				node.vertices[i].color.x = sceneMesh->mColors[0][i].r;
				node.vertices[i].color.y = sceneMesh->mColors[0][i].g;
				node.vertices[i].color.z = sceneMesh->mColors[0][i].b;
				node.vertices[i].color.w = sceneMesh->mColors[0][i].a;
			}
		}

		if (sceneMesh->HasFaces())
		{
			node.indices.resize(static_cast<size_t>(sceneMesh->mNumFaces) * 3);
			for (unsigned int i = 0; i < sceneMesh->mNumFaces; ++i)
			{
				unsigned int current = i * 3;
				node.indices[current++] = sceneMesh->mFaces[i].mIndices[0];
				node.indices[current++] = sceneMesh->mFaces[i].mIndices[1];
				node.indices[current] = sceneMesh->mFaces[i].mIndices[2];
			}
		}
	}
	return mesh;
}
