
#pragma once

#include "MathUtility.h"

struct Float3 : public InitializeZero<Float3> {
	union {
		struct { float F[3]; };
		struct { float X, Y, Z; };
	};
};

using Vector3F = Float3;