
#pragma once

struct Matrix : public InitializeZero<Matrix>
{
	union {
		float m[4][4];
	};

	void SetIdentity(void)
	{
		memset(this, 0, sizeof(Matrix));
		m[0][0] = 1.f; m[1][1] = 1.f; m[2][2] = 1.f; m[3][3] = 1.f;
	}

	using ThisType = Matrix;
	static void Add(const ThisType& left, const ThisType& right, ThisType& result)
	{
		for (int X = 0; X < 4; X++)
		{
			for (int Y = 0; Y < 4; Y++)
			{
				result.m[X][Y] = left.m[X][Y] + right.m[X][Y];
			}
		}
	}
	static void Subtract(const ThisType& left, const ThisType& right, ThisType& result);
	static void Multiply(const ThisType& left, const ThisType& right, ThisType& result);
	static void Devide(const ThisType& left, const ThisType& right, ThisType& result);
	static bool IsEqual(const ThisType& left, const ThisType& right);
	static void Inverse(const ThisType& target, ThisType& result);
	static void RemoveScale(const ThisType& target, ThisType& result);
};