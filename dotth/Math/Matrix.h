
#pragma once

struct Matrix : public InitializeZero<Matrix>
{
	union {
		struct {
			float _11, _12, _13, _14;
			float _21, _22, _23, _24;
			float _31, _32, _33, _34;
			float _41, _42, _43, _44;
		};
		float m[4][4];
	};
	Matrix(void)
	{

	}
	Matrix(float *f)
	{
		m[0][0] = f[0];
		m[0][1] = f[1];
		m[0][2] = f[2];
		m[0][3] = f[3];
		m[1][0] = f[4];
		m[1][1] = f[5];
		m[1][2] = f[6];
		m[1][3] = f[7];
		m[2][0] = f[8];
		m[2][1] = f[9];
		m[2][2] = f[10];
		m[2][3] = f[11];
		m[3][0] = f[12];
		m[3][1] = f[13];
		m[3][2] = f[14];
		m[3][3] = f[15];
	}

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