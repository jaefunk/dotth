
#pragma once

struct Matrix
{
	union {
		float f[16];
		float rc[4][4];
	};
	
	Matrix(void) = default;
	
	void SetZero(void)
	{
		memset(this, 0, sizeof(Matrix));
	}
	void SetIdentity(void)
	{
		memset(this, 0, sizeof(Matrix));
		rc[0][0] = 1.f; rc[1][1] = 1.f; rc[2][2] = 1.f; rc[3][3] = 1.f;
	}

	Matrix operator*(const Matrix& right)
	{
		Matrix Result;
		Matrix::Multiply(*this, right, Result);
		return Result;
	}

	static void GetRow(const Matrix& target, unsigned int index, Vector4& result)
	{
		unsigned int offset = 4 * index;
		result.x = target.f[0 + offset]; 
		result.y = target.f[1 + offset];
		result.z = target.f[2 + offset];
		result.w = target.f[3 + offset];
	}
	static void GetColumn(const Matrix& target, unsigned int index, Vector4& result)
	{
		result.x = target.f[0 + index];
		result.y = target.f[4 + index];
		result.z = target.f[8 + index];
		result.w = target.f[12 + index];
	}

	static void Multiply(const Matrix& left, const Vector4& right, Vector4& result)
	{
		Vector4 Row, Last;
		for (int r = 0; r < 4; r++)
		{
			Matrix::GetRow(left, r, Row);
			Vector4::Multiply(Row, right.f[r], Last);
			result.f[r] = Last.f[0] + Last.f[1] + Last.f[2] + Last.f[3];
		}
	}

	static void Multiply(const Matrix left, const Matrix right, Matrix& result)
	{
		result.SetZero();
		Vector4 Row, Col, Last;
		for (int r = 0; r < 4; r++)
		{
			for (int c = 0; c < 4; c++)
			{				
				Matrix::GetRow(right, r, Row);
				Matrix::GetColumn(left, c, Col);
				Vector4::Multiply(Row, Col, Last);
				result.rc[r][c] = Last.f[0] + Last.f[1] + Last.f[2] + Last.f[3];
			}
		}
	}

	static Matrix Scaling(float target)
	{
		Matrix Result;
		Result.SetIdentity();
		Result.rc[0][0] = target;
		Result.rc[1][1] = target;
		Result.rc[2][2] = target;
		return Result;
	}
	static Matrix Scaling(const Vector3& target)
	{
		Matrix Result;
		Result.SetIdentity();
		Result.rc[0][0] = target.x;
		Result.rc[1][1] = target.y;
		Result.rc[2][2] = target.z;
		return Result;
	}
	static Matrix RotatePitch(float radian)
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
	static Matrix RotateYaw(float radian)
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
	static Matrix RotateRoll(float radian)
	{
		Matrix Result;
		Result.SetIdentity();
		float cos = cosf(radian);
		float sin = sinf(radian);
		Result.rc[0][0] = cos; Result.rc[0][1] = -sin; 
		Result.rc[1][0] = sin; Result.rc[1][1] = cos; 
		return Result;
	}
	static Matrix Translate(const Vector3& target)
	{
		Matrix Result;
		Result.SetIdentity();
		Result.rc[0][3] = target.x;
		Result.rc[1][3] = target.y;
		Result.rc[2][3] = target.z;
		Result.rc[3][3] = 1.f;
		return Result;
	}

	float& operator[](int index)
	{
		return f[index];
	}
	float operator[](int index) const
	{
		return f[index];
	}
	operator DirectX::XMMATRIX()
	{
		return DirectX::XMMATRIX(f);
	}
	operator DirectX::XMMATRIX() const
	{
		return DirectX::XMMATRIX(f);
	}
};