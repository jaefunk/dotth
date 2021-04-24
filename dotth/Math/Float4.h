
struct Float4 : public InitializeZero<Float4> {
	union {
		struct { float F[4]; };
		struct { float X, Y, Z, W; };
		struct { float R, G, B, A; };
	};
	Float4(void)
	{

	}
	Float4(float _X, float _Y, float _Z, float _W)
	{
		X = _X;
		Y = _Y;
		Z = _Z;
		W = _W;
	}
};

using Vector4F = Float4;
using Color4F = Float4;