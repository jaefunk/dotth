#pragma once

#include "dotth.h"

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

enum class EXTENSION_TYPE {	
	JPEG,
	FBX,
};

struct R8G8B8A8 {
	union {
		struct {
			unsigned char R, G, B, A;
		};
		struct {
			unsigned int Alignment;
		};
	};

	R8G8B8A8(void) : Alignment(0)
	{

	}

	R8G8B8A8(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha)
		: R(red), G(green), B(blue), A(alpha)
	{
	}
};

struct Vertice {
	Vector3 position;
	Vector3 normal;
	Vector2 textureCoord;
	Vector3 tangent;
	Vector3 bitangent;
	Vector4 color;
};

class Resource
{
public:
	virtual std::shared_ptr<Resource> Clone(void) = 0;
};

class Mesh : public Resource
{
public:
	struct PrimitiveNode
	{
		unsigned int materialID;
		std::vector<Vertice> vertices;
		std::vector<unsigned int> indices;
		unsigned int GetVerticeByteWidth(void) const
		{
			return static_cast<unsigned int>(sizeof(Vertice) * vertices.size());
		}
		unsigned int GetIndiceByteWidth(void) const
		{
			return static_cast<unsigned int>(sizeof(unsigned int) * indices.size());
		}
	};
	std::vector<PrimitiveNode> primitiveNodes;

public:
	virtual std::shared_ptr<Resource> Clone(void) override
	{
		auto p = std::make_shared<Mesh>();
		p->primitiveNodes = this->primitiveNodes;
		return p;
	}
};

class SkinnedMesh : public Mesh
{
public:
	struct Weight
	{
		unsigned int vertexID = 0;
		float weight = 0.f;
	};
	struct Bone
	{
		std::string name;
		PrimitiveNode* primitiveNode;
		PrimitiveNode* armature;
		std::vector<Weight> weights;
		Matrix offsetMatrix;
	};
	std::vector<Bone> bones;

public:
	virtual std::shared_ptr<Resource> Clone(void) override
	{
		auto p = std::make_shared<SkinnedMesh>();
		p->primitiveNodes = this->primitiveNodes;
		p->bones = this->bones;
		return p;
	}
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
	unsigned int ComponentCount;
	unsigned int Width;
	unsigned int Height;
	std::vector<R8G8B8A8> Texels;

public:
	void* GetSysMem(void)
	{
		return static_cast<void*>(Texels.data());
	}
	unsigned int GetSysMemPitch(void)
	{
		return Width * static_cast<unsigned int>(sizeof(R8G8B8A8));
	}
};

class FBXLoader
{
public:
	static std::unique_ptr<Mesh> Load(const std::string& filePath);
};

class JPEGLoader
{
public:
	static std::unique_ptr<Texture> Load(const std::string& filePath);
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

		float& operator[](int index)
		{
			return f[index];
		}
		float operator[](int index) const
		{
			return f[index];
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
	};

	struct node
	{
		std::string name;

		matrix transformation;

		node* parent = nullptr;
		
		unsigned int numChildren = 0;
		node** children = nullptr;

		unsigned int numMeshes = 0;
		unsigned int** meshes = nullptr;

		node(const aiNode* raw)
		{
			name = raw->mName.C_Str();
			
			for (unsigned int i = 0; i < 16; ++i)
				transformation[i] = raw->mTransformation[i/4][i%4];
		
			parent = nullptr;
			numChildren = raw->mNumChildren;
			children = new node * [numChildren];
			for (unsigned int i = 0; i < numChildren; ++i)
			{
				children[i] = new node(raw->mChildren[i]);
				children[i]->parent = this;
			}
			
			

			raw->mNumMeshes;
			raw->mMeshes;
		}
		~node(void)
		{
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

		bone(const aiBone* raw)
		{
			name = raw->mName.C_Str();

			numWeights = raw->mNumWeights;
			weights = new weight[raw->mNumWeights];
			for (unsigned int i = 0; i < numWeights; ++i)
			{
				weights[i].vertexID = raw->mWeights[i].mVertexId;
				weights[i].value = raw->mWeights[i].mWeight;
			}

			raw->mArmature;
			raw->mNode;
		}
	};

	struct mesh
	{
		std::string name;
		
		unsigned int numVertices = 0;
		vertice* vertices = nullptr;

		unsigned int numIndices = 0;
		unsigned int* indices = nullptr;

		unsigned int numBones = 0;
		bone** bones = nullptr;

		unsigned int mateiralIndex = 0;

		mesh(const aiMesh* raw)
		{
			name = raw->mName.C_Str();

			numVertices = raw->mNumVertices;
			vertices = new vertice[numVertices];
			for (unsigned int i = 0; i < numVertices; ++i)
			{
				if (raw->HasPositions())
					vertices[i].position = vector3(raw->mVertices[i].x, -raw->mVertices[i].z, raw->mVertices[i].y);
				if (raw->HasNormals())
					vertices[i].normal = vector3(raw->mNormals[i].x, -raw->mNormals[i].z, raw->mNormals[i].y);
				if (raw->HasTextureCoords(0))
					vertices[i].textureCoord = vector2(raw->mTextureCoords[0][i].x, raw->mTextureCoords[0][i].y);
			}

			numIndices = raw->mNumFaces * 3;
			indices = new unsigned int[numIndices];
			for (unsigned int i = 0; i < raw->mNumFaces; ++i)
			{
				unsigned int current = i * 3;
				indices[current + 0] = raw->mFaces[i].mIndices[0];
				indices[current + 1] = raw->mFaces[i].mIndices[1];
				indices[current + 2] = raw->mFaces[i].mIndices[2];
			}

			numBones = raw->mNumBones;
			bones = new bone*[numBones];
			for (unsigned int i = 0; i < numBones; ++i)
				bones[i] = new bone(raw->mBones[i]);
		}
		~mesh(void)
		{
			if (numVertices && vertices)
				delete[] vertices;
			
			if (numIndices && indices)
				delete[] indices;

			if (numBones && bones)
				for (unsigned int i = 0; i < numBones; i++)
					delete bones[i];
			delete[] bones;
		}
	};

	struct material
	{
		material(const aiMaterial* raw)
		{

		}
	};

	template <class ty>
	struct keyframe
	{
		float time;
		ty value;
		bool operator==(const ty& rhs) const {
			return rhs.value == this->value;
		}
		bool operator!=(const ty& rhs) const {
			return value != this->value;
		}
		bool operator<(const ty& rhs) const {
			return time < rhs.time;
		}
		bool operator>(const ty& rhs) const {
			return time > rhs.time;
		}
	};

	struct morph
	{
	};

	template <>
	struct keyframe<morph>
	{
		float time;
		unsigned int* values;
		float* weights;
	};

	struct node_animation
	{
		std::string name;
		keyframe<vector3>* positionKeys;
		keyframe<vector4>* rotationKeys;
		keyframe<vector3>* scalingKeys;
	};

	struct morph_animation
	{
		std::string name;
		keyframe<morph>* morphKeys;
	};

	struct animation
	{
		std::string name;
		float duration;
		float tickPerSecond;
		node_animation** nodeChannels;
		morph_animation** morphChannels;

		animation(const aiAnimation* raw)
		{

		}
		~animation(void)
		{
		}
	};

	struct texture
	{
		std::string name;
		unsigned int width;
		unsigned int height;
		vector4* data;
		
		texture(const aiTexture* raw)
		{

		}
	};

	struct model
	{
		std::string name;

		node* root = nullptr;
		
		unsigned int numMeshes = 0;
		mesh** meshes = nullptr;

		unsigned int numMaterials = 0;
		material** materials = nullptr;

		unsigned int numAnimations = 0;
		animation** animations = nullptr;

		unsigned int numTextures = 0;
		texture** textures = nullptr;

		model(const aiScene* raw)
		{
			name = raw->mName.C_Str();

			root = new node(raw->mRootNode);

			numMeshes = raw->mNumMeshes;
			meshes = new mesh*[numMeshes];
			for (unsigned int i = 0; i < numMeshes; ++i)
				meshes[i] = new mesh(raw->mMeshes[i]);

			numMaterials = raw->mNumMaterials;
			materials = new material*[numMaterials];
			for (unsigned int i = 0; i < numMaterials; ++i)
				materials[i] = new material(raw->mMaterials[i]);

			numTextures = raw->mNumTextures;
			textures = new texture*[numTextures];
			for (unsigned int i = 0; i < numTextures; ++i)
				textures[i] = new texture(raw->mTextures[i]);

			numAnimations = raw->mNumAnimations;
			animations = new animation*[numAnimations];
			for (unsigned int i = 0; i < numAnimations; ++i)
				animations[i] = new animation(raw->mAnimations[i]);
		}

		~model(void)
		{
			delete root;

			if (numMeshes && meshes)
				for (unsigned int i = 0; i < numMeshes; i++)
					delete meshes[i];
			delete[] meshes;

			if (numMaterials && materials)
				for (unsigned int i = 0; i < numMaterials; i++)
					delete materials[i];
			delete[] materials;

			if (numTextures && textures)
				for (unsigned int i = 0; i < numTextures; i++)
					delete textures[i];
			delete[] textures;

			if (numAnimations && animations)
				for (unsigned int i = 0; i < numAnimations; i++)
					delete animations[i];
			delete[] animations;
		}
	};
}





