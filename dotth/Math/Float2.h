
#pragma once

#include "MathUtility.h"

struct Float2 : public InitializeZero<Float2> {
	union {
		struct { float F[]; };
		struct { float X, Y; };
	};
};

using Vector2F = Float2;