
#pragma once

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

#include "../dotth.h"
#include "Math.h"

namespace dotth2 {
	
	template<typename ty>
	struct value4 {
		union {
			struct {
				ty v[4];
			};
			struct {
				ty x, y, z, w;
			};
		};
		value4(void) = default;
		value4(ty _x, ty _y, ty _z, ty _w)
			: x(_x), y(_y), z(_z), w(_w)
		{
		}
	};

	class node 
	{
	public:
		std::string name;
		matrix local;
		matrix world;
		node* parent = nullptr;
		std::vector<node*> children;
		unsigned int depth = 0;

	public:
		node(const aiNode* raw, node* inParent = nullptr)
		{
			name = raw->mName.C_Str();
			
			for (unsigned int i = 0; i < 16; ++i)
				local[i] = raw->mTransformation[i % 4][i / 4];
			
			
			if (raw->mNumChildren != 0)
			{
				children.resize(raw->mNumChildren);
				for (unsigned int i = 0; i < raw->mNumChildren; ++i)
				{
					children[i] = new node(raw->mChildren[i], this);
				}
			}
			
			parent = inParent;
			node* p = inParent;
			while (p != nullptr)
			{
				depth++;
				p = p->parent;
			}
		}

		void foreach_all(std::function<void(node* one)> func)
		{
			func(this);
			for (node* child : children)
				child->foreach_all(func);
		}
	};

	class animation
	{
	public:
		animation(const aiAnimation* raw)
		{

		}
	};


	class mesh
	{
	public:
		std::string name;

		unsigned int mateiralIndex = 0;

		std::vector<vector3> positions;
		std::vector<vector3> normals;
		std::vector<vector2> textureCoords;
		std::vector<unsigned int> indices;
		std::vector<value4<int>> boneIds;
		std::vector<vector4> weights;

	public:
		mesh(const aiMesh* raw)
		{
			name = raw->mName.C_Str();

			if (raw->mNumVertices != 0)
			{
				positions.resize(raw->mNumVertices);
				normals.resize(raw->mNumVertices);
				textureCoords.resize(raw->mNumVertices);

				for (unsigned int i = 0; i < raw->mNumVertices; ++i)
				{
					positions[i] = vector3(raw->mVertices[i].x, raw->mVertices[i].y, raw->mVertices[i].z);
					normals[i] = vector3(raw->mNormals[i].x, raw->mNormals[i].y, raw->mNormals[i].z);
					textureCoords[i] = vector2(raw->mTextureCoords[0][i].x, raw->mTextureCoords[0][i].y);
				}
			}

			if (raw->mNumFaces != 0)
			{
				indices.resize(raw->mNumFaces * 3);
				for (unsigned int i = 0; i < raw->mNumFaces; ++i)
				{
					unsigned int current = i * 3;
					indices[current + 0] = raw->mFaces[i].mIndices[0];
					indices[current + 1] = raw->mFaces[i].mIndices[1];
					indices[current + 2] = raw->mFaces[i].mIndices[2];
				}
			}

			if (raw->mNumBones != 0)
			{
				boneIds.resize(raw->mNumVertices, value4<int>(-1, -1, -1, -1));
				weights.resize(raw->mNumVertices, vector4(0.f, 0.f, 0.f, 0.f));

				for (unsigned int i = 0; i < raw->mNumBones; ++i)
				{
					aiBone* Bone = raw->mBones[i];
					for (unsigned int j = 0; j < Bone->mNumWeights; ++j)
					{
						unsigned int vid = Bone->mWeights[j].mVertexId;
						float wei = Bone->mWeights[j].mWeight;
						for (unsigned int k = 0; k < 4; ++k)
						{
							if (boneIds[vid].v[k] < 0)
							{
								boneIds[vid].v[k] = i;
								weights[vid].f[k] = wei;
								break;
							}
						}
					}
				}
			}

			mateiralIndex = raw->mMaterialIndex;
		}
	};
	
	struct bone
	{
		int id;
		matrix offset;
	};

	class model 
	{
	public:
		std::map<std::string, node*> mapNodes;
		std::vector<node*> vecNodes;
		std::map<std::string, bone> mapBones;

	public:
		std::string name;
		node* root = nullptr;
		std::vector<mesh*> meshes;
		std::vector<animation*> animations;


	public:
		model(const aiScene* raw)
		{
			name = raw->mName.C_Str();
			
			if (raw->mRootNode != nullptr)
			{
				root = new node(raw->mRootNode);
				root->foreach_all(
					[this](node* one) {
						vecNodes.push_back(one);
						mapNodes.insert({ one->name, one });
					}
				);
				assert(mapNodes.size() == vecNodes.size());
			}

			if (raw->mNumMeshes != 0)
			{
				meshes.resize(raw->mNumMeshes);
				for (unsigned int i = 0; i < raw->mNumMeshes; ++i)
				{
					meshes[i] = new mesh(raw->mMeshes[i]);

					aiMesh* Mesh = raw->mMeshes[i];
					for (unsigned int j = 0; j < Mesh->mNumBones; ++j)
					{
						aiBone* Bone = Mesh->mBones[j];
						
						std::string boneName = Bone->mName.C_Str();
						bone b;
						b.id = mapBones.size();
						for (unsigned int k = 0; k < 16; ++k)
							b.offset[k] = Bone->mOffsetMatrix[k % 4][k / 4];
						mapBones.insert({ boneName, b });
					}
				}
			}
		}	
	};
}

namespace dotth2 {

}