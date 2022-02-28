
#pragma once

namespace dotth {
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
}
//struct Vector4 {
//	union {
//		struct { float f[4]; };
//		struct { float x, y, z, w; };
//	};
//
//	Vector4(void) = default;
//	Vector4(float f) : x(f), y(f), z(f), w(f) {}
//	Vector4(float* pf) : x(pf[0]), y(pf[1]), z(pf[2]), w(pf[3]) {}
//	Vector4(float _x, float _y, float _z, float _w) : x(_x), y(_y), z(_z), w(_w) {}
//	Vector4(const Vector4& value) : x(value.x), y(value.y), z(value.z), w(value.w) {}
//
//	static void Multiply(const Vector4& left, float right, Vector4& result)
//	{
//		result.x = left.x * right;
//		result.y = left.y * right;
//		result.z = left.z * right;
//		result.w = left.w * right;
//	}
//	static void Multiply(const Vector4& left, const Vector4& right, Vector4& result)
//	{
//		result.x = left.x * right.x;
//		result.y = left.y * right.y;
//		result.z = left.z * right.z;
//		result.w = left.w * right.w;
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