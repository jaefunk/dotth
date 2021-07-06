
#pragma once

//#undef  PI
//#define PI			(3.1415926535897932f)

// Copied from float.h
#define MAX_FLOAT	(3.402823466e+38F)
#define SMALL_FLOAT	(1.e-4f)

// Aux constants.
#define INV_PI		(0.31830988618f)
#define HALF_PI		(1.57079632679f)

// Common square roots
#define SQRT_2		(1.4142135623730950488016887242097f)
#define SQRT_3		(1.7320508075688772935274463415059f)
#define INV_SQRT_2	(0.70710678118654752440084436210485f)
#define INV_SQRT_3	(0.57735026918962576450914878050196f)
#define HALF_SQRT_2	(0.70710678118654752440084436210485f)
#define HALF_SQRT_3	(0.86602540378443864676372317075294f)

template <typename Ty>
struct InitializeZero {
	InitializeZero(void) {
		memset(this, 0, sizeof(Ty));
	}
};