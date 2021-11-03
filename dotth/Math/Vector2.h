
#pragma once

struct Vector2 {
	union {
		struct { float f[2]; };
		struct { float x, y; };
	};

	Vector2(void) = default;
	Vector2(float f) : x(f), y(f) {}
	Vector2(float* f) : x(f[0]), y(f[1]) {}
	Vector2(float _x, float _y) : x(_x), y(_y) {}
	Vector2(const Vector2& value) : x(value.x), y(value.y) {}

	float& operator[](int index)
	{
		return f[index];
	}
	float operator[](int index) const
	{
		return f[index];
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