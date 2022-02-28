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


class Resource
{
public:
	virtual std::shared_ptr<Resource> Clone(void) { return nullptr; };
};

namespace dotth {
	struct asset {
		virtual std::shared_ptr<dotth::asset> clone(void) = 0;
	};
	struct texture : public Resource {
		unsigned int width = 0;
		unsigned int height = 0;
		unsigned int componentCount = 0;
		std::vector<texel> texels;

		void* data(void)
		{
			return static_cast<void*>(texels.data());
		}
		unsigned int pitch(void)
		{
			return width * static_cast<unsigned int>(sizeof(texel));
		}
	};
}

namespace dotth
{
	//struct vector2 {
	//	union {
	//		struct { float f[2]; };
	//		struct { float x, y; };
	//	};

	//	vector2(void)
	//		: x(0.f), y(0.f)
	//	{
	//	}

	//	vector2(float f)
	//		: x(f), y(f)
	//	{
	//	}

	//	vector2(float* f)
	//		: x(f[0]), y(f[1])
	//	{
	//	}

	//	vector2(float _x, float _y)
	//		: x(_x), y(_y)
	//	{
	//	}

	//	static void add(const vector2& left, const vector2& right, vector2& result)
	//	{
	//		result.x = left.x + right.x;
	//		result.y = left.y + right.y;
	//	}

	//	static void subtract(const vector2& left, const vector2& right, vector2& result)
	//	{
	//		result.x = left.x - right.x;
	//		result.y = left.y - right.y;
	//	}

	//	static void multiply(const vector2& left, const vector2& right, vector2& result)
	//	{
	//		result.x = left.x * right.x;
	//		result.y = left.y * right.y;
	//	}

	//	static void multiply(const vector2& left, float right, vector2& result)
	//	{
	//		result.x = left.x * right;
	//		result.y = left.y * right;
	//	}

	//	static void devide(const vector2& left, float right, vector2& result)
	//	{
	//		result.x = left.x / right;
	//		result.y = left.y / right;
	//	}

	//	static bool equal(const vector2& left, const vector2& right, float tolerance = std::numeric_limits<float>::epsilon())
	//	{
	//		return abs(left.x - right.x) <= tolerance && abs(left.y - right.y) <= tolerance;
	//	}

	//	float& operator[](int index)
	//	{
	//		return f[index];
	//	}

	//	float operator[](int index) const
	//	{
	//		return f[index];
	//	}
	//};

	/*struct vector3 {
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
	};*/


	//struct vector4 {
	//	union {
	//		struct {
	//			float f[4];
	//		};

	//		struct {
	//			float x, y, z, w;
	//		};
	//	};

	//	vector4(void)
	//		: x(0.f), y(0.f), z(0.f), w(0.f)
	//	{
	//	}

	//	vector4(float f)
	//		: x(f), y(f), z(f), w(f)
	//	{
	//	}

	//	vector4(float* pf)
	//		: x(pf[0]), y(pf[1]), z(pf[2]), w(pf[3])
	//	{
	//	}

	//	vector4(float _x, float _y, float _z, float _w)
	//		: x(_x), y(_y), z(_z), w(_w)
	//	{
	//	}

	//	vector4(const vector4& value)
	//		: x(value.x), y(value.y), z(value.z), w(value.w)
	//	{
	//	}

	//	static void add(const vector4& left, const vector4& right, vector4& result)
	//	{
	//		result.x = left.x + right.x;
	//		result.y = left.y + right.y;
	//		result.z = left.z + right.z;
	//		result.w = left.w + right.w;
	//	}

	//	static void multiply(const vector4& left, float right, vector4& result)
	//	{
	//		result.x = left.x * right;
	//		result.y = left.y * right;
	//		result.z = left.z * right;
	//		result.w = left.w * right;
	//	}

	//	static void multiply(const vector4& left, const vector4& right, vector4& result)
	//	{
	//		result.x = left.x * right.x;
	//		result.y = left.y * right.y;
	//		result.z = left.z * right.z;
	//		result.w = left.w * right.w;
	//	}

	//	static bool equal(const vector4& left, const vector4& right, float tolerance = std::numeric_limits<float>::epsilon())
	//	{
	//		return abs(left.x - right.x) <= tolerance && abs(left.y - right.y) <= tolerance && abs(left.z - right.z) <= tolerance && abs(left.w - right.w) <= tolerance;
	//	}

	//	float& operator[](int index)
	//	{
	//		return f[index];
	//	}
	//	float operator[](int index) const
	//	{
	//		return f[index];
	//	}

	//	operator DirectX::XMFLOAT4()
	//	{
	//		return DirectX::XMFLOAT4(f);
	//	}
	//	operator DirectX::XMFLOAT4() const
	//	{
	//		return DirectX::XMFLOAT4(f);
	//	}
	//};

	//struct matrix
	//{
	//	union {
	//		float f[16];
	//		float rc[4][4];
	//	};

	//	matrix(void)
	//	{
	//		memset(this, 0, sizeof(matrix));
	//	}

	//	void set_zero(void)
	//	{
	//		memset(this, 0, sizeof(matrix));
	//	}

	//	void set_identity(void)
	//	{
	//		memset(this, 0, sizeof(matrix));
	//		rc[0][0] = 1.f; rc[1][1] = 1.f; rc[2][2] = 1.f; rc[3][3] = 1.f;
	//	}

	//	float determinant(void) const
	//	{
	//		return f[0] * f[5] * f[10] * f[15] - f[0] * f[5] * f[11] * f[14] + f[0] * f[6] * f[11] * f[13] - f[0] * f[6] * f[9] * f[15]
	//			+ f[0] * f[7] * f[9] * f[14] - f[0] * f[7] * f[10] * f[13] - f[1] * f[6] * f[11] * f[12] + f[1] * f[6] * f[8] * f[15]
	//			- f[1] * f[7] * f[8] * f[14] + f[1] * f[7] * f[10] * f[12] - f[1] * f[4] * f[10] * f[15] + f[1] * f[4] * f[11] * f[14]
	//			+ f[2] * f[7] * f[8] * f[13] - f[2] * f[7] * f[9] * f[12] + f[2] * f[4] * f[9] * f[15] - f[2] * f[4] * f[11] * f[13]
	//			+ f[2] * f[5] * f[11] * f[12] - f[2] * f[5] * f[8] * f[15] - f[3] * f[4] * f[9] * f[14] + f[3] * f[4] * f[10] * f[13]
	//			- f[3] * f[5] * f[10] * f[12] + f[3] * f[5] * f[8] * f[14] - f[3] * f[6] * f[8] * f[13] + f[3] * f[6] * f[9] * f[12];
	//	}

	//	matrix transpose(void)
	//	{
	//		matrix m = *this;
	//		std::swap((float&)m.f[4], (float&)m.f[1]);
	//		std::swap((float&)m.f[8], (float&)m.f[2]);
	//		std::swap((float&)m.f[9], (float&)m.f[6]);
	//		std::swap((float&)m.f[12], (float&)m.f[3]);
	//		std::swap((float&)m.f[13], (float&)m.f[7]);
	//		std::swap((float&)m.f[14], (float&)m.f[11]);
	//		return m;
	//	}

	//	matrix inverse(void)
	//	{
	//		float det = determinant();
	//		if (det == 0.f)
	//		{
	//			float nan = std::numeric_limits<float>::quiet_NaN();

	//			return *this;
	//		}
	//		const float invdet = 1.f / det;
	//		matrix result;
	//		float a1 = f[0];
	//		float a2 = f[1];
	//		float a3 = f[2];
	//		float a4 = f[3];
	//		float b1 = f[4];
	//		float b2 = f[5];
	//		float b3 = f[6];
	//		float b4 = f[7];
	//		float c1 = f[8];
	//		float c2 = f[9];
	//		float c3 = f[10];
	//		float c4 = f[11];
	//		float d1 = f[12];
	//		float d2 = f[13];
	//		float d3 = f[14];
	//		float d4 = f[15];

	//		result.f[0] = invdet * (b2 * (c3 * d4 - c4 * d3) + b3 * (c4 * d2 - c2 * d4) + b4 * (c2 * d3 - c3 * d2));
	//		result.f[1] = -invdet * (a2 * (c3 * d4 - c4 * d3) + a3 * (c4 * d2 - c2 * d4) + a4 * (c2 * d3 - c3 * d2));
	//		result.f[2] = invdet * (a2 * (b3 * d4 - b4 * d3) + a3 * (b4 * d2 - b2 * d4) + a4 * (b2 * d3 - b3 * d2));
	//		result.f[3] = -invdet * (a2 * (b3 * c4 - b4 * c3) + a3 * (b4 * c2 - b2 * c4) + a4 * (b2 * c3 - b3 * c2));
	//		result.f[4] = -invdet * (b1 * (c3 * d4 - c4 * d3) + b3 * (c4 * d1 - c1 * d4) + b4 * (c1 * d3 - c3 * d1));
	//		result.f[5] = invdet * (a1 * (c3 * d4 - c4 * d3) + a3 * (c4 * d1 - c1 * d4) + a4 * (c1 * d3 - c3 * d1));
	//		result.f[6] = -invdet * (a1 * (b3 * d4 - b4 * d3) + a3 * (b4 * d1 - b1 * d4) + a4 * (b1 * d3 - b3 * d1));
	//		result.f[7] = invdet * (a1 * (b3 * c4 - b4 * c3) + a3 * (b4 * c1 - b1 * c4) + a4 * (b1 * c3 - b3 * c1));
	//		result.f[8] = invdet * (b1 * (c2 * d4 - c4 * d2) + b2 * (c4 * d1 - c1 * d4) + b4 * (c1 * d2 - c2 * d1));
	//		result.f[9] = -invdet * (a1 * (c2 * d4 - c4 * d2) + a2 * (c4 * d1 - c1 * d4) + a4 * (c1 * d2 - c2 * d1));
	//		result.f[10] = invdet * (a1 * (b2 * d4 - b4 * d2) + a2 * (b4 * d1 - b1 * d4) + a4 * (b1 * d2 - b2 * d1));
	//		result.f[11] = -invdet * (a1 * (b2 * c4 - b4 * c2) + a2 * (b4 * c1 - b1 * c4) + a4 * (b1 * c2 - b2 * c1));
	//		result.f[12] = -invdet * (b1 * (c2 * d3 - c3 * d2) + b2 * (c3 * d1 - c1 * d3) + b3 * (c1 * d2 - c2 * d1));
	//		result.f[13] = invdet * (a1 * (c2 * d3 - c3 * d2) + a2 * (c3 * d1 - c1 * d3) + a3 * (c1 * d2 - c2 * d1));
	//		result.f[14] = -invdet * (a1 * (b2 * d3 - b3 * d2) + a2 * (b3 * d1 - b1 * d3) + a3 * (b1 * d2 - b2 * d1));
	//		result.f[15] = invdet * (a1 * (b2 * c3 - b3 * c2) + a2 * (b3 * c1 - b1 * c3) + a3 * (b1 * c2 - b2 * c1));
	//		return result;
	//	}

	//	matrix operator*(const matrix& right)
	//	{
	//		matrix result;
	//		matrix::multiply(*this, right, result);
	//		return result;
	//	}

	//	static void get_row(const matrix& target, unsigned int index, vector4& result)
	//	{
	//		unsigned int offset = 4 * index;
	//		result.x = target.f[0 + offset];
	//		result.y = target.f[1 + offset];
	//		result.z = target.f[2 + offset];
	//		result.w = target.f[3 + offset];
	//	}

	//	static void get_column(const matrix& target, unsigned int index, vector4& result)
	//	{
	//		result.x = target.f[0 + index];
	//		result.y = target.f[4 + index];
	//		result.z = target.f[8 + index];
	//		result.w = target.f[12 + index];
	//	}

	//	static void multiply(const matrix& left, const vector4& right, vector4& result)
	//	{
	//		vector4 row, last;
	//		for (int r = 0; r < 4; r++)
	//		{
	//			matrix::get_row(left, r, row);
	//			vector4::multiply(row, right.f[r], last);
	//			result.f[r] = last.f[0] + last.f[1] + last.f[2] + last.f[3];
	//		}
	//	}

	//	static void multiply(const matrix left, const matrix right, matrix& result)
	//	{
	//		result.set_zero();
	//		vector4 row, col, last;
	//		for (int r = 0; r < 4; r++)
	//		{
	//			for (int c = 0; c < 4; c++)
	//			{
	//				matrix::get_row(left, r, row);
	//				matrix::get_column(right, c, col);
	//				vector4::multiply(row, col, last);
	//				result.rc[r][c] = last.f[0] + last.f[1] + last.f[2] + last.f[3];
	//			}
	//		}
	//	}

	//	static matrix scaling(float target)
	//	{
	//		matrix result;
	//		result.set_identity();
	//		result.rc[0][0] = target;
	//		result.rc[1][1] = target;
	//		result.rc[2][2] = target;
	//		return result;
	//	}

	//	static matrix scaling(const vector3& target)
	//	{
	//		matrix result;
	//		result.set_identity();
	//		result.rc[0][0] = target.x;
	//		result.rc[1][1] = target.y;
	//		result.rc[2][2] = target.z;
	//		return result;
	//	}

	//	static matrix rotate_pitch(float radian)
	//	{
	//		matrix result;
	//		result.set_identity();
	//		float cos = cosf(radian);
	//		float sin = sinf(radian);
	//		result.rc[1][1] = cos;
	//		result.rc[1][2] = -sin;
	//		result.rc[2][1] = sin;
	//		result.rc[2][2] = cos;
	//		return result;
	//	}

	//	static matrix rotate_yaw(float radian)
	//	{
	//		matrix result;
	//		result.set_identity();
	//		float cos = cosf(radian);
	//		float sin = sinf(radian);
	//		result.rc[0][0] = cos;
	//		result.rc[0][2] = sin;
	//		result.rc[2][0] = -sin;
	//		result.rc[2][2] = cos;
	//		return result;
	//	}

	//	static matrix rotate_roll(float radian)
	//	{
	//		matrix result;
	//		result.set_identity();
	//		float cos = cosf(radian);
	//		float sin = sinf(radian);
	//		result.rc[0][0] = cos; result.rc[0][1] = -sin;
	//		result.rc[1][0] = sin; result.rc[1][1] = cos;
	//		return result;
	//	}

	//	static matrix translate(const vector3& target)
	//	{
	//		matrix result;
	//		result.set_identity();
	//		result.rc[0][3] = target.x;
	//		result.rc[1][3] = target.y;
	//		result.rc[2][3] = target.z;
	//		result.rc[3][3] = 1.f;
	//		return result;
	//	}

	//	float& operator[](int index)
	//	{
	//		return f[index];
	//	}

	//	float operator[](int index) const
	//	{
	//		return f[index];
	//	}

	//	void operator=(XMMATRIX value)
	//	{
	//		memcpy(f, value.r, sizeof(float) * 16);
	//	}
	//	void operator=(XMFLOAT4X4 value)
	//	{
	//		memcpy(f, value.m, sizeof(float) * 16);
	//	}

	//	operator DirectX::XMMATRIX() const
	//	{
	//		return DirectX::XMMATRIX(f);
	//	}

	//	operator DirectX::XMFLOAT4X4() const
	//	{
	//		return DirectX::XMFLOAT4X4(f);
	//	}
	//};

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
		matrix transformation;
		node* parent = nullptr;
		std::vector<node*> children;
		unsigned int depth = 0;

	public:
		node(const aiNode* raw, node* inParent = nullptr)
		{
			name = raw->mName.C_Str();

			for (unsigned int i = 0; i < 16; ++i)
				transformation[i] = raw->mTransformation[i % 4][i / 4];

			parent = inParent;
			if (raw->mNumChildren != 0)
			{
				children.resize(raw->mNumChildren);
				for (unsigned int i = 0; i < raw->mNumChildren; ++i)
				{
					children[i] = new node(raw->mChildren[i], this);
				}
			}

			node* p = parent;
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
		int id;
		matrix offset;
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

	//struct material
	//{
	//	material(const aiMaterial* raw)
	//	{

	//	}
	//};

	//struct keyframe
	//{
	//	float time;
	//	vector3 position;
	//	vector4 rotation;
	//	vector3 scale;
	//};

	//namespace anim
	//{
	//	struct node
	//	{
	//		std::string name;
	//		unsigned int numKeys = 0;
	//		keyframe* keyframes = nullptr;

	//		node(aiNodeAnim* raw)
	//		{
	//			name = raw->mNodeName.C_Str();

	//			numKeys = raw->mNumPositionKeys;
	//			if (numKeys != 0)
	//			{
	//				keyframes = new keyframe[numKeys];
	//				for (unsigned int i = 0; i < numKeys; ++i)
	//				{
	//					keyframes[i].time = static_cast<float>(raw->mPositionKeys[i].mTime);

	//					aiVector3D position = raw->mPositionKeys[i].mValue;
	//					keyframes[i].position = vector3(position.x, position.y, position.z);
	//					aiQuaternion rotation = raw->mRotationKeys[i].mValue;
	//					keyframes[i].rotation = vector4(rotation.x, rotation.y, rotation.z, rotation.w);
	//					aiVector3D scale = raw->mScalingKeys[i].mValue;
	//					keyframes[i].scale = vector3(scale.x, scale.y, scale.z);
	//				}
	//			}
	//		}
	//		~node(void)
	//		{
	//			if (numKeys && keyframes)
	//				delete[] keyframes;
	//		}
	//	};
	//}

	//struct animation
	//{
	//	std::string name;
	//	float duration = 0.f;
	//	float tickPerSecond = 0.f;

	//	unsigned int numNodeChannels = 0;
	//	anim::node** nodeChannels = nullptr;

	//	animation(const aiAnimation* raw)
	//	{
	//		name = raw->mName.C_Str();
	//		duration = static_cast<float>(raw->mDuration);
	//		tickPerSecond = static_cast<float>(raw->mTicksPerSecond);

	//		numNodeChannels = raw->mNumChannels;
	//		if (numNodeChannels)
	//		{
	//			nodeChannels = new anim::node * [numNodeChannels];
	//			for (unsigned int i = 0; i < numNodeChannels; ++i)
	//			{
	//				nodeChannels[i] = new anim::node(raw->mChannels[i]);
	//			}
	//		}
	//	}
	//	~animation(void)
	//	{
	//	}
	//};

	class model : public Resource
	{
	public:
		std::map<std::string, node*> mapNodes;
		std::vector<node*> vecNodes;
		std::map<std::string, bone> mapBones;

	public:
		std::string name;
		node* root = nullptr;
		std::vector<mesh*> meshes;
		//std::vector<animation*> animations;
		matrix globalInverse;

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
				std::sort(vecNodes.begin(), vecNodes.end(), [](const node* l, const node* r) {

					return l->depth > r->depth;
					});

				globalInverse = root->transformation.inverse();
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
						b.id = static_cast<int>(mapBones.size());
						for (unsigned int k = 0; k < 16; ++k)
							b.offset[k] = Bone->mOffsetMatrix[k % 4][k / 4];
						mapBones.insert({ boneName, b });
					}
				}
			}


		}
	};
}

class FBXLoader
{
public:
	static std::shared_ptr<dotth::model> Load(const std::string& filePath);
	//static std::shared_ptr<dotth2::model> Load2(const std::string& filePath);
};

class JPEGLoader
{
public:
	static std::shared_ptr<dotth::texture> Load(const std::string& filePath);
};

