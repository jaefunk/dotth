#pragma once

#include "dotth.h"

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

#include "libjpeg/include/jpeglib.h"



enum class EXTENSION_TYPE {
	JPEG,
	FBX,
};

struct texel {
	union {
		struct {
			unsigned char r, g, b, a;
		};
		struct {
			unsigned int alignment;
		};
	};

	texel(void) : alignment(0)
	{

	}

	texel(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha = 255)
		: r(red), g(green), b(blue), a(alpha)
	{
	}
};

namespace dotth {
	struct asset {
		virtual std::shared_ptr<dotth::asset> clone(void) = 0;
	};
	struct texture : public asset {
		unsigned int width = 0;
		unsigned int height = 0;
		texel* texels = nullptr;

		texture(jpeg_decompress_struct* raw)
		{
			width = raw->image_width;
			height = raw->image_height;


			unsigned int byteSize = raw->output_width * raw->output_height * raw->num_components;
			unsigned char* buffer = new unsigned char[byteSize];
			unsigned char* position = buffer;
			while (raw->output_scanline < raw->image_height)
			{
				jpeg_read_scanlines(raw, &position, 1);
				int address = raw->output_width * raw->output_components;
				position += address;
			}

			unsigned int num = width * height;
			texels = new texel[num];
			int distance = 0;
			position = buffer;
			for (unsigned int i = 0; i < num; ++i)
			{
				texels[i].r = *(position++);
				texels[i].g = *(position++);
				texels[i].b = *(position++);
				texels[i].a = 255;
				position += raw->output_components;
			}

			delete[] buffer;
		}

		~texture(void)
		{
			if (width != 0 && height != 0 && texels != nullptr)
				delete[] texels;
		}

		void* data(void)
		{
			return static_cast<void*>(texels);
		}
		unsigned int pitch(void)
		{
			return width * static_cast<unsigned int>(sizeof(texel));
		}
	};
}
class Resource
{
public:
	virtual std::shared_ptr<Resource> Clone(void) = 0;
};

class Texture : public Resource
{
public:
	virtual std::shared_ptr<Resource> Clone(void) override
	{
		auto p = std::make_shared<Texture>();
		p->ComponentCount = this->ComponentCount;
		p->Width = this->Width;
		p->Height = this->Height;
		p->Texels = this->Texels;
		return p;
	}

public:
	unsigned int ComponentCount = 0;
	unsigned int Width = 0;
	unsigned int Height = 0;
	std::vector<texel> Texels;

public:
	void* GetSysMem(void)
	{
		return static_cast<void*>(Texels.data());
	}
	unsigned int GetSysMemPitch(void)
	{
		return Width * static_cast<unsigned int>(sizeof(texel));
	}
};

namespace dotth
{
	struct vector2 {
		union {
			struct { float f[2]; };
			struct { float x, y; };
		};

		vector2(void)
			: x(0.f), y(0.f)
		{
		}

		vector2(float f)
			: x(f), y(f)
		{
		}

		vector2(float* f)
			: x(f[0]), y(f[1])
		{
		}

		vector2(float _x, float _y)
			: x(_x), y(_y)
		{
		}

		static void add(const vector2& left, const vector2& right, vector2& result)
		{
			result.x = left.x + right.x;
			result.y = left.y + right.y;
		}

		static void subtract(const vector2& left, const vector2& right, vector2& result)
		{
			result.x = left.x - right.x;
			result.y = left.y - right.y;
		}

		static void multiply(const vector2& left, const vector2& right, vector2& result)
		{
			result.x = left.x * right.x;
			result.y = left.y * right.y;
		}

		static void multiply(const vector2& left, float right, vector2& result)
		{
			result.x = left.x * right;
			result.y = left.y * right;
		}

		static void devide(const vector2& left, float right, vector2& result)
		{
			result.x = left.x / right;
			result.y = left.y / right;
		}

		static bool equal(const vector2& left, const vector2& right, float tolerance = std::numeric_limits<float>::epsilon())
		{
			return abs(left.x - right.x) <= tolerance && abs(left.y - right.y) <= tolerance;
		}

		float& operator[](int index)
		{
			return f[index];
		}

		float operator[](int index) const
		{
			return f[index];
		}
	};

	struct vector3 {
		union {
			struct {
				float f[3];
			};

			struct {
				float x, y, z;
			};
		};

		vector3(void)
			: x(0.f), y(0.f), z(0.f)
		{
		}

		vector3(float f)
			: x(f), y(f), z(f)
		{
		}

		vector3(float* pf)
			: x(pf[0]), y(pf[1]), z(pf[2])
		{
		}

		vector3(float _x, float _y, float _z)
			: x(_x), y(_y), z(_z)
		{
		}

		static void add(const vector3& left, const vector3& right, vector3& result)
		{
			result.x = left.x + right.x;
			result.y = left.y + right.y;
			result.z = left.z + right.z;
		}

		static void subtract(const vector3& left, const vector3& right, vector3& result)
		{
			result.x = left.x - right.x;
			result.y = left.y - right.y;
			result.z = left.z - right.z;
		}

		static void multiply(const vector3& left, const vector3& right, vector3& result)
		{
			result.x = left.x * right.x;
			result.y = left.y * right.y;
			result.z = left.z * right.z;
		}

		static void multiply(const vector3& left, float right, vector3& result)
		{
			result.x = left.x * right;
			result.y = left.y * right;
			result.z = left.z * right;
		}

		static void devide(const vector3& left, float right, vector3& result)
		{
			result.x = left.x / right;
			result.y = left.y / right;
			result.z = left.z / right;
		}

		static bool equal(const vector3& left, const vector3& right, float tolerance = std::numeric_limits<float>::epsilon())
		{
			return abs(left.x - right.x) <= tolerance && abs(left.y - right.y) <= tolerance && abs(left.z - right.z) <= tolerance;
		}

		float& operator[](int index)
		{
			return f[index];
		}

		float operator[](int index) const
		{
			return f[index];
		}

		operator DirectX::XMFLOAT3()
		{
			return DirectX::XMFLOAT3(f);
		}
		operator DirectX::XMFLOAT3() const
		{
			return DirectX::XMFLOAT3(f);
		}
	};


	struct vector4 {
		union {
			struct {
				float f[4];
			};

			struct {
				float x, y, z, w;
			};
		};

		vector4(void)
			: x(0.f), y(0.f), z(0.f), w(0.f)
		{
		}

		vector4(float f)
			: x(f), y(f), z(f), w(f)
		{
		}

		vector4(float* pf)
			: x(pf[0]), y(pf[1]), z(pf[2]), w(pf[3])
		{
		}

		vector4(float _x, float _y, float _z, float _w)
			: x(_x), y(_y), z(_z), w(_w)
		{
		}

		vector4(const vector4& value)
			: x(value.x), y(value.y), z(value.z), w(value.w)
		{
		}

		static void add(const vector4& left, const vector4& right, vector4& result)
		{
			result.x = left.x + right.x;
			result.y = left.y + right.y;
			result.z = left.z + right.z;
			result.w = left.w + right.w;
		}

		static void multiply(const vector4& left, float right, vector4& result)
		{
			result.x = left.x * right;
			result.y = left.y * right;
			result.z = left.z * right;
			result.w = left.w * right;
		}

		static void multiply(const vector4& left, const vector4& right, vector4& result)
		{
			result.x = left.x * right.x;
			result.y = left.y * right.y;
			result.z = left.z * right.z;
			result.w = left.w * right.w;
		}

		static bool equal(const vector4& left, const vector4& right, float tolerance = std::numeric_limits<float>::epsilon())
		{
			return abs(left.x - right.x) <= tolerance && abs(left.y - right.y) <= tolerance && abs(left.z - right.z) <= tolerance && abs(left.w - right.w) <= tolerance;
		}

		float& operator[](int index)
		{
			return f[index];
		}
		float operator[](int index) const
		{
			return f[index];
		}

		operator DirectX::XMFLOAT4()
		{
			return DirectX::XMFLOAT4(f);
		}
		operator DirectX::XMFLOAT4() const
		{
			return DirectX::XMFLOAT4(f);
		}
	};

	struct matrix
	{
		union {
			float f[16];
			float rc[4][4];
		};

		matrix(void) = default;

		void set_zero(void)
		{
			memset(this, 0, sizeof(matrix));
		}

		void set_identity(void)
		{
			memset(this, 0, sizeof(matrix));
			rc[0][0] = 1.f; rc[1][1] = 1.f; rc[2][2] = 1.f; rc[3][3] = 1.f;
		}

		matrix operator*(const matrix& right)
		{
			matrix result;
			matrix::multiply(*this, right, result);
			return result;
		}

		static void get_row(const matrix& target, unsigned int index, vector4& result)
		{
			unsigned int offset = 4 * index;
			result.x = target.f[0 + offset];
			result.y = target.f[1 + offset];
			result.z = target.f[2 + offset];
			result.w = target.f[3 + offset];
		}

		static void get_column(const matrix& target, unsigned int index, vector4& result)
		{
			result.x = target.f[0 + index];
			result.y = target.f[4 + index];
			result.z = target.f[8 + index];
			result.w = target.f[12 + index];
		}

		static void multiply(const matrix& left, const vector4& right, vector4& result)
		{
			vector4 row, last;
			for (int r = 0; r < 4; r++)
			{
				matrix::get_row(left, r, row);
				vector4::multiply(row, right.f[r], last);
				result.f[r] = last.f[0] + last.f[1] + last.f[2] + last.f[3];
			}
		}

		static void multiply(const matrix left, const matrix right, matrix& result)
		{
			result.set_zero();
			vector4 row, col, last;
			for (int r = 0; r < 4; r++)
			{
				for (int c = 0; c < 4; c++)
				{
					matrix::get_row(right, r, row);
					matrix::get_column(left, c, col);
					vector4::multiply(row, col, last);
					result.rc[r][c] = last.f[0] + last.f[1] + last.f[2] + last.f[3];
				}
			}
		}

		static matrix scaling(float target)
		{
			matrix result;
			result.set_identity();
			result.rc[0][0] = target;
			result.rc[1][1] = target;
			result.rc[2][2] = target;
			return result;
		}

		static matrix scaling(const vector3& target)
		{
			matrix result;
			result.set_identity();
			result.rc[0][0] = target.x;
			result.rc[1][1] = target.y;
			result.rc[2][2] = target.z;
			return result;
		}

		static matrix rotate_pitch(float radian)
		{
			matrix result;
			result.set_identity();
			float cos = cosf(radian);
			float sin = sinf(radian);
			result.rc[1][1] = cos;
			result.rc[1][2] = -sin;
			result.rc[2][1] = sin;
			result.rc[2][2] = cos;
			return result;
		}

		static matrix rotate_yaw(float radian)
		{
			matrix result;
			result.set_identity();
			float cos = cosf(radian);
			float sin = sinf(radian);
			result.rc[0][0] = cos;
			result.rc[0][2] = sin;
			result.rc[2][0] = -sin;
			result.rc[2][2] = cos;
			return result;
		}

		static matrix rotate_roll(float radian)
		{
			matrix result;
			result.set_identity();
			float cos = cosf(radian);
			float sin = sinf(radian);
			result.rc[0][0] = cos; result.rc[0][1] = -sin;
			result.rc[1][0] = sin; result.rc[1][1] = cos;
			return result;
		}

		static matrix translate(const vector3& target)
		{
			matrix result;
			result.set_identity();
			result.rc[0][3] = target.x;
			result.rc[1][3] = target.y;
			result.rc[2][3] = target.z;
			result.rc[3][3] = 1.f;
			return result;
		}

		float& operator[](int index)
		{
			return f[index];
		}

		float operator[](int index) const
		{
			return f[index];
		}

		void operator=(XMMATRIX value)
		{
			memcpy(f, value.r, sizeof(float) * 16);
		}
	};


	struct node
	{
		std::string name;

		matrix local;
		matrix world;

		node* parent = nullptr;

		unsigned int numChildren = 0;
		node** children = nullptr;

		unsigned int depth = 0;
		unsigned int numMeshes = 0;
		unsigned int* meshes = nullptr;

		node(const aiNode* raw, node* inParent = nullptr)
		{
			name = raw->mName.C_Str();
			for (unsigned int i = 0; i < 16; ++i)
				local[i] = raw->mTransformation[i / 4][i % 4];

			parent = inParent;
			numChildren = raw->mNumChildren;
			if (numChildren != 0)
			{
				children = new node * [numChildren];
				for (unsigned int i = 0; i < numChildren; ++i)
				{
					children[i] = new node(raw->mChildren[i], this);
				}
			}

			numMeshes = raw->mNumMeshes;
			if (numMeshes != 0)
			{
				meshes = new unsigned int[numMeshes];
				for (unsigned int i = 0; i < numChildren; ++i)
					meshes[i] = raw->mMeshes[i];
			}

			node* p = parent;
			while (p != nullptr)
			{
				depth++;
				p = p->parent;
			}
		}

		~node(void)
		{
			if (numChildren && children)
				for (unsigned int i = 0; i < numChildren; ++i)
					delete children[i];
			delete[] children;
			delete[] meshes;
		}

		node* find(const std::string& inName)
		{
			if (inName.empty())
				return nullptr;
			if (!strcmp(name.c_str(), inName.c_str()))
				return this;
			for (unsigned int i = 0; i < numChildren; ++i)
			{
				node* p = children[i]->find(inName);
				if (p)
					return p;
			}
			return nullptr;
		}

		void foreach_all(std::function<void(node* one)> func)
		{
			func(this);
			for (unsigned int i = 0; i < numChildren; ++i)
				children[i]->foreach_all(func);
		}
	};

	struct vertice
	{
		vector3 position;
		vector3 normal;
		vector2 textureCoord;
	};

	struct weight
	{
		unsigned int vertexID = 0;
		float value = 0.f;
	};

	struct bone
	{
		std::string name;

		unsigned int numWeights;
		weight* weights;

		node* armature;
		node* targetNode;

		matrix offset;

		bone(const aiBone* raw, node* root = nullptr)
		{
			name = raw->mName.C_Str();

			numWeights = raw->mNumWeights;
			if (numWeights != 0)
			{
				weights = new weight[raw->mNumWeights];
				for (unsigned int i = 0; i < numWeights; ++i)
				{
					weights[i].vertexID = raw->mWeights[i].mVertexId;
					weights[i].value = raw->mWeights[i].mWeight;
				}
			}

			for (unsigned int i = 0; i < 16; ++i)
				offset[i] = raw->mOffsetMatrix[i / 4][i % 4];

			if (root != nullptr)
			{
				if (raw->mArmature)
					armature = root->find(raw->mArmature->mName.C_Str());
				if (raw->mNode)
					targetNode = root->find(raw->mNode->mName.C_Str());
			}
		}
		~bone(void)
		{
			if (weights && numWeights)
				delete[] weights;
		}
	};

	template<typename ty>
	struct value4 {
		ty x, y, z, w;
		value4(void) = default;
		value4(ty _x, ty _y, ty _z, ty _w)
			: x(_x), y(_y), z(_z), w(_w)
		{
		}
	};
	struct uint4 {
		unsigned int x = 0;
		unsigned int y = 0;
		unsigned int z = 0;
		unsigned int w = 0;
	};

	struct BoneInfo {
		int id;
		dotth::matrix offset;
	};
	
	
	struct mesh
	{
		std::string name;

		unsigned int numVertices = 0;
		vertice* vertices = nullptr;

		unsigned int numPositions = 0;
		vector3* positions;
		unsigned int numNormals = 0;
		vector3* normals;
		unsigned int numTextureCoords = 0;
		vector2* textureCoords;

		unsigned int numIndices = 0;
		unsigned int* indices = nullptr;

		unsigned int numBones = 0;
		bone** bones = nullptr;

		unsigned int numBoneIds = 0;
		value4<int>* boneids = nullptr;
		vector4* weights = nullptr;

		unsigned int mateiralIndex = 0;

		mesh(std::map<std::string, BoneInfo>& boneInfos, const aiMesh* raw, node* root = nullptr)
		{
			name = raw->mName.C_Str();

			numPositions = numNormals = numTextureCoords = raw->mNumVertices;
			if (numPositions != 0)
			{
				if (numPositions != 0)
					positions = new vector3[numPositions];
				if (numNormals != 0)
					normals = new vector3[numNormals];
				if (numTextureCoords != 0)
					textureCoords = new vector2[numTextureCoords];

				for (unsigned int i = 0; i < numPositions; ++i)
				{
					positions[i] = vector3(raw->mVertices[i].x, raw->mVertices[i].y, raw->mVertices[i].z);
					normals[i] = vector3(raw->mNormals[i].x, raw->mNormals[i].y, raw->mNormals[i].z);
					textureCoords[i] = vector2(raw->mTextureCoords[0][i].x, raw->mTextureCoords[0][i].y);
				}
			}

			numIndices = raw->mNumFaces * 3;
			if (numIndices != 0)
			{
				indices = new unsigned int[numIndices];
				for (unsigned int i = 0; i < raw->mNumFaces; ++i)
				{
					unsigned int current = i * 3;
					indices[current + 0] = raw->mFaces[i].mIndices[0];
					indices[current + 1] = raw->mFaces[i].mIndices[1];
					indices[current + 2] = raw->mFaces[i].mIndices[2];
				}
			}

			mateiralIndex = raw->mMaterialIndex;

			numBones = raw->mNumBones;
			if (numBones != 0)
			{
				bones = new bone * [numBones];
				for (unsigned int i = 0; i < numBones; ++i)
				{
					bones[i] = new bone(raw->mBones[i], root);
				}

				numBoneIds = numPositions;
				boneids = new value4<int>[numBoneIds];
				weights = new vector4[numBoneIds];
				for (unsigned int i = 0; i < numBoneIds; ++i)
				{
					boneids[i] = value4<int>(-1, -1, -1, -1);
					weights[i] = vector4(0.f, 0.f, 0.f, 0.f);
				}
				for (unsigned int i = 0; i < numBones; ++i)
				{
					int boneID = -1;
					std::string boneName = bones[i]->name;
					if (boneInfos.find(boneName) == boneInfos.end())
					{
						BoneInfo boneInfo;
						boneInfo.id = boneInfos.size();
						boneInfo.offset = bones[i]->offset;
						boneInfos[boneName] = boneInfo;
						boneID = boneInfos.size();
					}
					else
					{
						boneID = boneInfos[boneName].id;
					}
					assert(boneID != -1);
					unsigned int numWeights = bones[i]->numWeights;
					for (unsigned int weightIndex = 0; weightIndex < numWeights; ++weightIndex)
					{
						unsigned int vertexId = bones[i]->weights[weightIndex].vertexID;
						float weight = bones[i]->weights[weightIndex].value;
						
						assert(vertexId <= numBoneIds);
						
						for (unsigned int j = 0; j < 4; ++j)
						{
							if (boneids[vertexId].x < 0)
							{
								boneids[vertexId].x = boneID;
								weights[vertexId].x = weight;
							}
						}
					}
				}
			}
		}
		~mesh(void)
		{
			if (numVertices && vertices)
				delete[] vertices;
			if (numPositions && positions)
				delete[] positions;
			if (numNormals && normals)
				delete[] normals;
			if (numTextureCoords && textureCoords)
				delete[] textureCoords;

			if (numIndices && indices)
				delete[] indices;

			if (numBones && bones)
				for (unsigned int i = 0; i < numBones; i++)
					delete bones[i];
			delete[] bones;

			if (numBoneIds && boneids && weights)
			{
				delete[] boneids;
				delete[] weights;
			}
		}

		unsigned int GetVerticeByteWidth(void) const
		{
			return static_cast<unsigned int>(sizeof(vertice) * numVertices);
		}
		unsigned int GetIndiceByteWidth(void) const
		{
			return static_cast<unsigned int>(sizeof(unsigned int) * numIndices);
		}
	};

	struct material
	{
		material(const aiMaterial* raw)
		{

		}
	};

	struct keyframe
	{
		float time;
		vector3 position;
		vector4 rotation;
		vector3 scale;
	};

	namespace anim
	{
		struct node
		{
			std::string name;
			unsigned int numKeys = 0;
			keyframe* keyframes = nullptr;

			node(aiNodeAnim* raw)
			{
				name = raw->mNodeName.C_Str();

				numKeys = raw->mNumPositionKeys;
				if (numKeys != 0)
				{
					keyframes = new keyframe[numKeys];
					for (unsigned int i = 0; i < numKeys; ++i)
					{
						keyframes[i].time = static_cast<float>(raw->mPositionKeys[i].mTime);

						aiVector3D position = raw->mPositionKeys[i].mValue;
						keyframes[i].position = vector3(position.x, position.y, position.z);
						aiQuaternion rotation = raw->mRotationKeys[i].mValue;
						keyframes[i].rotation = vector4(rotation.x, rotation.y, rotation.z, rotation.w);
						aiVector3D scale = raw->mScalingKeys[i].mValue;
						keyframes[i].scale = vector3(scale.x, scale.y, scale.z);
					}
				}
			}
			~node(void)
			{
				if (numKeys && keyframes)
					delete[] keyframes;
			}
		};
	}

	struct animation
	{
		std::string name;
		float duration = 0.f;
		float tickPerSecond = 0.f;

		unsigned int numNodeChannels = 0;
		anim::node** nodeChannels = nullptr;

		animation(const aiAnimation* raw)
		{
			name = raw->mName.C_Str();
			duration = static_cast<float>(raw->mDuration);
			tickPerSecond = static_cast<float>(raw->mTicksPerSecond);

			numNodeChannels = raw->mNumChannels;
			if (numNodeChannels)
			{
				nodeChannels = new anim::node * [numNodeChannels];
				for (unsigned int i = 0; i < numNodeChannels; ++i)
				{
					nodeChannels[i] = new anim::node(raw->mChannels[i]);
				}
			}
		}
		~animation(void)
		{
		}
	};

	struct model : public Resource
	{
	private:
		const aiScene* scene;
		std::map<std::string, node*> nodes;
	public:
		std::string name;

		node* root = nullptr;

		unsigned int numMeshes = 0;
		mesh** meshes = nullptr;

		unsigned int numAnimations = 0;
		animation** animations = nullptr;

		std::map<std::string, BoneInfo> boneInfos;
		int boneCount = 0;

		model(const aiScene* raw)
			: scene(raw)
		{
			name = raw->mName.C_Str();

			root = new node(raw->mRootNode);
			root->foreach_all(
				[this](node* one) {
					nodes.insert({ one->name, one });
				}
			);

			numMeshes = raw->mNumMeshes;
			if (numMeshes != 0)
			{
				meshes = new mesh * [numMeshes];
				for (unsigned int i = 0; i < numMeshes; ++i)
				{
					meshes[i] = new mesh(boneInfos, raw->mMeshes[i], root);
					for (unsigned int j = 0; j < meshes[i]->numBones; ++j)
					{
						{
							auto finded = nodes.find(raw->mMeshes[i]->mBones[j]->mArmature->mName.C_Str());
							if (finded != nodes.end())
								meshes[i]->bones[j]->armature = finded->second;
						}
						{
							auto finded = nodes.find(raw->mMeshes[i]->mBones[j]->mNode->mName.C_Str());
							if (finded != nodes.end())
								meshes[i]->bones[j]->targetNode = finded->second;
						}
					}
				}
			}

			numAnimations = raw->mNumAnimations;
			if (numAnimations != 0)
			{
				animations = new animation * [numAnimations];
				for (unsigned int i = 0; i < numAnimations; ++i)
					animations[i] = new animation(raw->mAnimations[i]);
			}
		}

		~model(void)
		{
			delete root;

			if (numMeshes && meshes)
				for (unsigned int i = 0; i < numMeshes; i++)
					delete meshes[i];
			delete[] meshes;

			if (numAnimations && animations)
				for (unsigned int i = 0; i < numAnimations; i++)
					delete animations[i];
			delete[] animations;
		}

		std::shared_ptr<Resource> Clone(void)
		{
			auto p = std::make_shared<model>(scene);
			return p;
		}
	};
}

#include "new/Asset.h"

class FBXLoader
{
public:
	static std::shared_ptr<dotth::model> Load(const std::string& filePath);
	static std::shared_ptr<dotth2::model> Load2(const std::string& filePath);
};

class JPEGLoader
{
public:
	static std::shared_ptr<Texture> Load(const std::string& filePath);
};

