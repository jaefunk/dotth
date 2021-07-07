
#pragma once

#undef ELEMENTCOUNT
#define ELEMENTCOUNT 4

struct Float4 {
	union {
		struct { float f[4]; };
		struct { float x, y, z, w; };
		struct { float r, g, b, a; };
	};
	Float4(void) = default;
	Float4(const Float3& float3, float _w)
		: Float4(float3.x, float3.y, float3.z, _w)
	{

	}
	Float4(float _x, float _y, float _z, float _w)
		: x(_x), y(_y), z(_z), w(_w)
	{
	}
	Float4(unsigned char _r, unsigned char _g, unsigned char _b, unsigned char _a)
		: x(_r/255.f), y(_g / 255.f), z(_b / 255.f), w(_a / 255.f)
	{
	}
	using ThisType = Float4;
	static void Multiply(const ThisType& left, const float& right, ThisType& result)
	{
		for (int index = 0; index < ELEMENTCOUNT; ++index)
			result[index] = left[index] * right;
	}
	static void Multiply(const ThisType& left, const ThisType& right, ThisType& result)
	{
		for (int index = 0; index < ELEMENTCOUNT; ++index)
			result[index] = left[index] * right[index];
	}
	operator DirectX::XMFLOAT4()
	{
		return DirectX::XMFLOAT4(f);
	}
	operator DirectX::XMFLOAT4() const
	{
		return DirectX::XMFLOAT4(f);
	}

private:
	float& operator[](int index) { return f[index]; }
	float operator[](int index) const { return f[index]; }
};

using Vector4F = Float4;
using Color4F = Float4;