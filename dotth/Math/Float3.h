
#pragma once

#include "../D3D11.h"

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
	operator DirectX::XMFLOAT3()
	{
		return DirectX::XMFLOAT3(f);
	}
	operator DirectX::XMFLOAT3() const
	{
		return DirectX::XMFLOAT3(f);
	}
};

using Vector3F = Float3;