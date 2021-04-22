
#pragma once

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
};

using Vector3F = Float3;