
#pragma once

struct Float2 : public InitializeZero<Float2> {
	union {
		struct { float F[2]; };
		struct { float X, Y; };
		struct { float U, V; };
	};
};

using Vector2F = Float2;