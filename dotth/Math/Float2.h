
#pragma once

#include "../D3D11.h"

struct Float2 : public InitializeZero<Float2> {
	union {
		struct { float f[2]; };
		struct { float x, y; };
		struct { float u, v; };
	};
	Float2(void) = default;
	Float2(const float* _f)
		: x(_f[0]), y(_f[1])
	{
	}
	Float2(float _x, float _y)
		: x(_x), y(_y)
	{
	}
	operator DirectX::XMFLOAT2()
	{
		return DirectX::XMFLOAT2(f);
	}
	operator DirectX::XMFLOAT2() const
	{
		return DirectX::XMFLOAT2(f);
	}
};

using Vector2F = Float2;