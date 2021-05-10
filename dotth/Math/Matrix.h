
#pragma once

struct Matrix : public InitializeZero<Matrix>
{
	union {
		float m[4][4];
	};

	FORCEINLINE void SetIdentity(void)
	{
		memset(this, 0, sizeof(Matrix));
		m[0][0] = 1.f; m[1][1] = 1.f; m[2][2] = 1.f; m[3][3] = 1.f;
	}
};