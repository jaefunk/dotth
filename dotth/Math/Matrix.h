
#pragma once

struct Matrix
{
	union {
		float f[16];
		float rc[4][4];
	};
	
	Matrix(void)
	{

	}
	
	void SetZero(void)
	{
		memset(this, 0, sizeof(Matrix));
	}
	void SetIdentity(void)
	{
		memset(this, 0, sizeof(Matrix));
		rc[0][0] = 1.f; rc[1][1] = 1.f; rc[2][2] = 1.f; rc[3][3] = 1.f;
	}

	operator DirectX::XMMATRIX()
	{
		return DirectX::XMMATRIX(f);
	}
	operator DirectX::XMMATRIX() const
	{
		return DirectX::XMMATRIX(f);
	}
	Matrix operator*(const Matrix& right)
	{
		Matrix Result;
		Matrix::Multiply(*this, right, Result);
		return Result;
	}

	using ThisType = Matrix;
	static void Row(const ThisType& target, unsigned int index, Float4& result)
	{
		unsigned int offset = 4 * index;
		result.x = target.f[0 + offset]; 
		result.y = target.f[1 + offset];
		result.z = target.f[2 + offset];
		result.w = target.f[3 + offset];
	}
	static void Column(const ThisType& target, unsigned int index, Float4& result)
	{
		result.x = target.f[0 + index];
		result.y = target.f[4 + index];
		result.z = target.f[8 + index];
		result.w = target.f[12 + index];
	}

	static void Multiply(const ThisType& left, const Float4& right, Float4& result)
	{
		for (int r = 0; r < 4; r++)
		{
			Float4 Row, Last;
			Matrix::Row(left, r, Row);
			Float4::Multiply(Row, right.f[r], Last);
			result.f[r] = Last.f[0] + Last.f[1] + Last.f[2] + Last.f[3];
		}
	}

	static void Multiply(const ThisType& left, const ThisType& right, ThisType& result)
	{
		result.SetZero();
		for (int r = 0; r < 4; r++)
		{
			for (int c = 0; c < 4; c++)
			{
				Float4 Row, Col, Last;
				Matrix::Row(left, r, Row);
				Matrix::Column(right, c, Col);
				Float4::Multiply(Row, Col, Last);
				result.rc[r][c] = Last.f[0] + Last.f[1] + Last.f[2] + Last.f[3];
			}
		}
	}

	static Matrix Scaling(const float& target)
	{
		Matrix Result;
		Result.SetIdentity();
		Result.rc[0][0] = target;
		Result.rc[1][1] = target;
		Result.rc[2][2] = target;
		return Result;
	}
	static Matrix Scaling(const Float3& target)
	{
		Matrix Result;
		Result.SetIdentity();
		Result.rc[0][0] = target.x;
		Result.rc[1][1] = target.y;
		Result.rc[2][2] = target.z;
		return Result;
	}
	static Matrix RotatePitch(const float& radian)
	{
		Matrix Result;
		Result.SetIdentity();
		float cos = cosf(radian);
		float sin = sinf(radian);
		Result.rc[1][1] = cos; 
		Result.rc[1][2] = -sin;
		Result.rc[2][1] = sin; 
		Result.rc[2][2] = cos;
		return Result;
	}
	static Matrix RotateYaw(const float& radian)
	{
		Matrix Result;
		Result.SetIdentity();
		float cos = cosf(radian);
		float sin = sinf(radian);		
		Result.rc[0][0] = cos; 
		Result.rc[0][2] = sin;
		Result.rc[2][0] = -sin; 
		Result.rc[2][2] = cos;
		return Result;
	}
	static Matrix RotateRoll(const float& radian)
	{
		Matrix Result;
		Result.SetIdentity();
		float cos = cosf(radian);
		float sin = sinf(radian);
		Result.rc[0][0] = cos; Result.rc[0][1] = -sin; 
		Result.rc[1][0] = sin; Result.rc[1][1] = cos; 
		return Result;
	}
	static Matrix Translate(const Float3& target)
	{
		Matrix Result;
		Result.SetIdentity();
		Result.rc[0][3] = target.x;
		Result.rc[1][3] = target.y;
		Result.rc[2][3] = target.z;
		Result.rc[3][3] = 1.f;
		return Result;
	}

	
};