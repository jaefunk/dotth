#include "Asset3D.h"
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"


unsigned int section::GetVerticeByteWidth(void) const
{
	return static_cast<unsigned int>(sizeof(decltype(vertices)::value_type) * vertices.size());
}
unsigned int section::GetIndiceByteWidth(void) const
{
	return static_cast<unsigned int>(sizeof(decltype(indices)::value_type) * indices.size());
}

bool model::LoadWithAssimp(const std::string& path)
{
	Assimp::Importer importer;
	auto scene = importer.ReadFile(path, aiProcess_ConvertToLeftHanded | aiProcess_Triangulate | aiProcess_OptimizeMeshes);
	if (scene == nullptr)
		return false;

	sections.resize(scene->mNumMeshes);
	for (unsigned int index = 0; index < scene->mNumMeshes; ++index)
	{
		auto mesh = scene->mMeshes[index];
		sections[index].vertices.resize(mesh->mNumVertices);
		for (unsigned int i = 0; i < mesh->mNumVertices; ++i)
		{
			if (mesh->HasPositions())
			{
				sections[index].vertices[i].position.x = mesh->mVertices[i].x;
				sections[index].vertices[i].position.y = -mesh->mVertices[i].z;
				sections[index].vertices[i].position.z = mesh->mVertices[i].y;
			}

			if (mesh->HasNormals())
			{
				sections[index].vertices[i].normal.x = mesh->mNormals[i].x;
				sections[index].vertices[i].normal.y = -mesh->mNormals[i].z;
				sections[index].vertices[i].normal.z = mesh->mNormals[i].y;
			}

			if (mesh->HasTangentsAndBitangents())
			{
				sections[index].vertices[i].tangent.x = mesh->mTangents[i].x;
				sections[index].vertices[i].tangent.y = mesh->mTangents[i].y;
				sections[index].vertices[i].tangent.z = mesh->mTangents[i].z;
			}

			if (mesh->HasTangentsAndBitangents())
			{
				sections[index].vertices[i].bitangent.x = mesh->mBitangents[i].x;
				sections[index].vertices[i].bitangent.y = mesh->mBitangents[i].y;
				sections[index].vertices[i].bitangent.z = mesh->mBitangents[i].z;
			}

			if (mesh->HasTextureCoords(0))
			{
				sections[index].vertices[i].textureCoord.x = mesh->mTextureCoords[0][i].x;
				sections[index].vertices[i].textureCoord.y = mesh->mTextureCoords[0][i].y;
			}

			if (mesh->HasVertexColors(0))
			{
				sections[index].vertices[i].color.r = mesh->mColors[0][i].r;
				sections[index].vertices[i].color.g = mesh->mColors[0][i].g;
				sections[index].vertices[i].color.b = mesh->mColors[0][i].b;
				sections[index].vertices[i].color.a = mesh->mColors[0][i].a;
			}
		}

		if (mesh->HasFaces())
			sections[index].indices.resize(mesh->mNumFaces * 3);
		for (unsigned int i = 0; i < mesh->mNumFaces; ++i)
		{
			unsigned int current = i * 3;
			sections[index].indices[current + 0] = mesh->mFaces[i].mIndices[0];
			sections[index].indices[current + 1] = mesh->mFaces[i].mIndices[1];
			sections[index].indices[current + 2] = mesh->mFaces[i].mIndices[2];
		}
	}
	//sections.clear();
	//section s;
	//vertice v;

	//v.position = Float3(-1.f, 1.f, 0.f);
	//v.textureCoord = Float2(0.f, 0.f);
	//v.color = Float4(1.f, 0.f, 0.f, 1.f);
	//s.vertices.push_back(v);

	//v.position = Float3(1.f, 1.f, 0.f);
	//v.textureCoord = Float2(1.f, 0.f);
	//v.color = Float4(0.f, 1.f, 0.f, 1.f);
	//s.vertices.push_back(v);
	//
	//v.position = Float3(-1.f, -1.f, 0.f);
	//v.textureCoord = Float2(0.f, 1.f);
	//v.color = Float4(0.f, 0.f, 1.f, 1.f);
	//s.vertices.push_back(v);
	//
	//v.position = Float3(1.f, -1.f, 0.f);
	//v.textureCoord = Float2(1.f, 1.f);
	//v.color = Float4(1.f, 1.f, 1.f, 1.f);
	//s.vertices.push_back(v);

	//s.indices.push_back(0);
	//s.indices.push_back(1);
	//s.indices.push_back(2);

	//s.indices.push_back(1);
	//s.indices.push_back(3);
	//s.indices.push_back(2);

	//s.textureIndex = 0;

	//sections.push_back(s);
	return true;
}