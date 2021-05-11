
#pragma once

#include "../D3D11.h"

#define ELEMENTCOUNT 3
struct Float3 : public InitializeZero<Float3> {
	union {
		struct { float f[3]; };
		struct { float x, y, z; };
	};
	Float3(void) = default;
	Float3(float _x, float _y, float _z)
		: x(_x), y(_y), z(_z)
	{
	}

	using ThisType = Float3;
	static void Add(const ThisType& left, const ThisType& right, ThisType& result)
	{
		for (int index = 0; index < ELEMENTCOUNT; ++index)
			result[index] = left[index] + right[index];
	}
	static void Subtract(const ThisType& left, const ThisType& right, ThisType& result)
	{
		for (int index = 0; index < ELEMENTCOUNT; ++index)
			result[index] = left[index] - right[index];
	}
	static void Multiply(const ThisType& left, const float& right, ThisType& result)
	{
		for (int index = 0; index < ELEMENTCOUNT; ++index)
			result[index] = left[index] * right;
	}
	static void Devide(const ThisType& left, const float& right, ThisType& result)
	{
		for (int index = 0; index < ELEMENTCOUNT; ++index)
			result[index] = left[index] / right;
	}
	static bool IsEqual(const ThisType& left, const ThisType& right, float tolerance = SMALL_FLOAT)
	{
		for (int index = 0; index < ELEMENTCOUNT; ++index)
		{
			if (left[index] - right[index] > SMALL_FLOAT)
			{
				return false;
			}
		}
		return true;
	}
	static void Inverse(const ThisType& target, ThisType& result)
	{
		Float3::Multiply(target, -1.f, result);
	}

	operator DirectX::XMFLOAT3()
	{
		return DirectX::XMFLOAT3(f);
	}
	operator DirectX::XMFLOAT3() const
	{
		return DirectX::XMFLOAT3(f);
	}

private:
	float& operator[](int index) { return f[index]; }
	float operator[](int index) const { return f[index]; }
};

using Vector3F = Float3;