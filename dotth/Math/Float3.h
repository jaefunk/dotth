
#pragma once

#include "../D3D11.h"

struct Float3 : public InitializeZero<Float3> {
	union {
		struct { float F[3]; };
		struct { float X, Y, Z; };
	};
	Float3(void)
	{

	}
	Float3(float _X, float _Y, float _Z)
	{
		X = _X;
		Y = _Y;
		Z = _Z;
	}
	operator DirectX::XMFLOAT3()
	{
		return DirectX::XMFLOAT3(F);
	}
	operator DirectX::XMFLOAT3() const
	{
		return DirectX::XMFLOAT3(F);
	}
};

using Vector3F = Float3;