
#pragma once

struct Float4 : public InitializeZero<Float4> {
	union {
		struct { float f[4]; };
		struct { float x, y, z, w; };
		struct { float r, g, b, a; };
	};
	Float4(void) = default;
	Float4(float _x, float _y, float _z, float _w)
		: x(_x), y(_y), z(_z), w(_w)
	{
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

using Vector4F = Float4;
using Color4F = Float4;