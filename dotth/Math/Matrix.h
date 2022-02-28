
#pragma once

//#include "Vector4.h"

namespace dotth {
	struct matrix
	{
		union {
			float f[16];
			float rc[4][4];
		};

		matrix(void)
		{
			memset(this, 0, sizeof(matrix));
		}

		void set_zero(void)
		{
			memset(this, 0, sizeof(matrix));
		}

		void set_identity(void)
		{
			memset(this, 0, sizeof(matrix));
			rc[0][0] = 1.f; rc[1][1] = 1.f; rc[2][2] = 1.f; rc[3][3] = 1.f;
		}

		float determinant(void) const
		{
			return f[0] * f[5] * f[10] * f[15] - f[0] * f[5] * f[11] * f[14] + f[0] * f[6] * f[11] * f[13] - f[0] * f[6] * f[9] * f[15]
				+ f[0] * f[7] * f[9] * f[14] - f[0] * f[7] * f[10] * f[13] - f[1] * f[6] * f[11] * f[12] + f[1] * f[6] * f[8] * f[15]
				- f[1] * f[7] * f[8] * f[14] + f[1] * f[7] * f[10] * f[12] - f[1] * f[4] * f[10] * f[15] + f[1] * f[4] * f[11] * f[14]
				+ f[2] * f[7] * f[8] * f[13] - f[2] * f[7] * f[9] * f[12] + f[2] * f[4] * f[9] * f[15] - f[2] * f[4] * f[11] * f[13]
				+ f[2] * f[5] * f[11] * f[12] - f[2] * f[5] * f[8] * f[15] - f[3] * f[4] * f[9] * f[14] + f[3] * f[4] * f[10] * f[13]
				- f[3] * f[5] * f[10] * f[12] + f[3] * f[5] * f[8] * f[14] - f[3] * f[6] * f[8] * f[13] + f[3] * f[6] * f[9] * f[12];
		}

		matrix transpose(void) const
		{
			matrix m = *this;
			std::swap((float&)m.f[4], (float&)m.f[1]);
			std::swap((float&)m.f[8], (float&)m.f[2]);
			std::swap((float&)m.f[9], (float&)m.f[6]);
			std::swap((float&)m.f[12], (float&)m.f[3]);
			std::swap((float&)m.f[13], (float&)m.f[7]);
			std::swap((float&)m.f[14], (float&)m.f[11]);
			return m;
		}

		matrix inverse(void) const
		{
			float det = determinant();
			if (det == 0.f)
			{
				float nan = std::numeric_limits<float>::quiet_NaN();

				return *this;
			}
			const float invdet = 1.f / det;
			matrix result;
			float a1 = f[0];
			float a2 = f[1];
			float a3 = f[2];
			float a4 = f[3];
			float b1 = f[4];
			float b2 = f[5];
			float b3 = f[6];
			float b4 = f[7];
			float c1 = f[8];
			float c2 = f[9];
			float c3 = f[10];
			float c4 = f[11];
			float d1 = f[12];
			float d2 = f[13];
			float d3 = f[14];
			float d4 = f[15];

			result.f[0] = invdet * (b2 * (c3 * d4 - c4 * d3) + b3 * (c4 * d2 - c2 * d4) + b4 * (c2 * d3 - c3 * d2));
			result.f[1] = -invdet * (a2 * (c3 * d4 - c4 * d3) + a3 * (c4 * d2 - c2 * d4) + a4 * (c2 * d3 - c3 * d2));
			result.f[2] = invdet * (a2 * (b3 * d4 - b4 * d3) + a3 * (b4 * d2 - b2 * d4) + a4 * (b2 * d3 - b3 * d2));
			result.f[3] = -invdet * (a2 * (b3 * c4 - b4 * c3) + a3 * (b4 * c2 - b2 * c4) + a4 * (b2 * c3 - b3 * c2));
			result.f[4] = -invdet * (b1 * (c3 * d4 - c4 * d3) + b3 * (c4 * d1 - c1 * d4) + b4 * (c1 * d3 - c3 * d1));
			result.f[5] = invdet * (a1 * (c3 * d4 - c4 * d3) + a3 * (c4 * d1 - c1 * d4) + a4 * (c1 * d3 - c3 * d1));
			result.f[6] = -invdet * (a1 * (b3 * d4 - b4 * d3) + a3 * (b4 * d1 - b1 * d4) + a4 * (b1 * d3 - b3 * d1));
			result.f[7] = invdet * (a1 * (b3 * c4 - b4 * c3) + a3 * (b4 * c1 - b1 * c4) + a4 * (b1 * c3 - b3 * c1));
			result.f[8] = invdet * (b1 * (c2 * d4 - c4 * d2) + b2 * (c4 * d1 - c1 * d4) + b4 * (c1 * d2 - c2 * d1));
			result.f[9] = -invdet * (a1 * (c2 * d4 - c4 * d2) + a2 * (c4 * d1 - c1 * d4) + a4 * (c1 * d2 - c2 * d1));
			result.f[10] = invdet * (a1 * (b2 * d4 - b4 * d2) + a2 * (b4 * d1 - b1 * d4) + a4 * (b1 * d2 - b2 * d1));
			result.f[11] = -invdet * (a1 * (b2 * c4 - b4 * c2) + a2 * (b4 * c1 - b1 * c4) + a4 * (b1 * c2 - b2 * c1));
			result.f[12] = -invdet * (b1 * (c2 * d3 - c3 * d2) + b2 * (c3 * d1 - c1 * d3) + b3 * (c1 * d2 - c2 * d1));
			result.f[13] = invdet * (a1 * (c2 * d3 - c3 * d2) + a2 * (c3 * d1 - c1 * d3) + a3 * (c1 * d2 - c2 * d1));
			result.f[14] = -invdet * (a1 * (b2 * d3 - b3 * d2) + a2 * (b3 * d1 - b1 * d3) + a3 * (b1 * d2 - b2 * d1));
			result.f[15] = invdet * (a1 * (b2 * c3 - b3 * c2) + a2 * (b3 * c1 - b1 * c3) + a3 * (b1 * c2 - b2 * c1));
			return result;
		}

		matrix operator*(const matrix& right)
		{
			matrix result;
			matrix::multiply(*this, right, result);
			return result;
		}

		static void get_row(const matrix& target, unsigned int index, vector4& result)
		{
			unsigned int offset = 4 * index;
			result.x = target.f[0 + offset];
			result.y = target.f[1 + offset];
			result.z = target.f[2 + offset];
			result.w = target.f[3 + offset];
		}

		static void get_column(const matrix& target, unsigned int index, vector4& result)
		{
			result.x = target.f[0 + index];
			result.y = target.f[4 + index];
			result.z = target.f[8 + index];
			result.w = target.f[12 + index];
		}

		static void multiply(const matrix& left, const vector4& right, vector4& result)
		{
			vector4 row, last;
			for (int r = 0; r < 4; r++)
			{
				matrix::get_row(left, r, row);
				vector4::multiply(row, right.f[r], last);
				result.f[r] = last.f[0] + last.f[1] + last.f[2] + last.f[3];
			}
		}

		static void multiply(const matrix left, const matrix right, matrix& result)
		{
			result.set_zero();
			vector4 row, col, last;
			for (int r = 0; r < 4; r++)
			{
				for (int c = 0; c < 4; c++)
				{
					matrix::get_row(left, r, row);
					matrix::get_column(right, c, col);
					vector4::multiply(row, col, last);
					result.rc[r][c] = last.f[0] + last.f[1] + last.f[2] + last.f[3];
				}
			}
		}

		static matrix scaling(float target)
		{
			matrix result;
			result.set_identity();
			result.rc[0][0] = target;
			result.rc[1][1] = target;
			result.rc[2][2] = target;
			return result;
		}

		static matrix scaling(const vector3& target)
		{
			matrix result;
			result.set_identity();
			result.rc[0][0] = target.x;
			result.rc[1][1] = target.y;
			result.rc[2][2] = target.z;
			return result;
		}

		static matrix rotate_pitch(float radian)
		{
			matrix result;
			result.set_identity();
			float cos = cosf(radian);
			float sin = sinf(radian);
			result.rc[1][1] = cos;
			result.rc[1][2] = -sin;
			result.rc[2][1] = sin;
			result.rc[2][2] = cos;
			return result;
		}

		static matrix rotate_yaw(float radian)
		{
			matrix result;
			result.set_identity();
			float cos = cosf(radian);
			float sin = sinf(radian);
			result.rc[0][0] = cos;
			result.rc[0][2] = sin;
			result.rc[2][0] = -sin;
			result.rc[2][2] = cos;
			return result;
		}

		static matrix rotate_roll(float radian)
		{
			matrix result;
			result.set_identity();
			float cos = cosf(radian);
			float sin = sinf(radian);
			result.rc[0][0] = cos; result.rc[0][1] = -sin;
			result.rc[1][0] = sin; result.rc[1][1] = cos;
			return result;
		}

		static matrix translate(const vector3& target)
		{
			matrix result;
			result.set_identity();
			result.rc[0][3] = target.x;
			result.rc[1][3] = target.y;
			result.rc[2][3] = target.z;
			result.rc[3][3] = 1.f;
			return result;
		}

		float& operator[](int index)
		{
			return f[index];
		}

		float operator[](int index) const
		{
			return f[index];
		}

		void operator=(XMMATRIX value)
		{
			memcpy(f, value.r, sizeof(float) * 16);
		}
		void operator=(XMFLOAT4X4 value)
		{
			memcpy(f, value.m, sizeof(float) * 16);
		}

		operator DirectX::XMMATRIX() const
		{
			return DirectX::XMMATRIX(f);
		}

		operator DirectX::XMFLOAT4X4() const
		{
			return DirectX::XMFLOAT4X4(f);
		}
	};
}
//
//struct Matrix
//{
//	union {
//		float f[16];
//		float rc[4][4];
//	};
//	
//	Matrix(void) = default;
//	
//	void SetZero(void)
//	{
//		memset(this, 0, sizeof(Matrix));
//	}
//	void SetIdentity(void)
//	{
//		memset(this, 0, sizeof(Matrix));
//		rc[0][0] = 1.f; rc[1][1] = 1.f; rc[2][2] = 1.f; rc[3][3] = 1.f;
//	}
//
//	Matrix operator*(const Matrix& right)
//	{
//		Matrix Result;
//		Matrix::Multiply(*this, right, Result);
//		return Result;
//	}
//
//	static void GetRow(const Matrix& target, unsigned int index, Vector4& result)
//	{
//		unsigned int offset = 4 * index;
//		result.x = target.f[0 + offset]; 
//		result.y = target.f[1 + offset];
//		result.z = target.f[2 + offset];
//		result.w = target.f[3 + offset];
//	}
//	static void GetColumn(const Matrix& target, unsigned int index, Vector4& result)
//	{
//		result.x = target.f[0 + index];
//		result.y = target.f[4 + index];
//		result.z = target.f[8 + index];
//		result.w = target.f[12 + index];
//	}
//
//	static void Multiply(const Matrix& left, const Vector4& right, Vector4& result)
//	{
//		Vector4 Row, Last;
//		for (int r = 0; r < 4; r++)
//		{
//			Matrix::GetRow(left, r, Row);
//			Vector4::Multiply(Row, right.f[r], Last);
//			result.f[r] = Last.f[0] + Last.f[1] + Last.f[2] + Last.f[3];
//		}
//	}
//
//	static void Multiply(const Matrix left, const Matrix right, Matrix& result)
//	{
//		result.SetZero();
//		Vector4 Row, Col, Last;
//		for (int r = 0; r < 4; r++)
//		{
//			for (int c = 0; c < 4; c++)
//			{				
//				Matrix::GetRow(right, r, Row);
//				Matrix::GetColumn(left, c, Col);
//				Vector4::Multiply(Row, Col, Last);
//				result.rc[r][c] = Last.f[0] + Last.f[1] + Last.f[2] + Last.f[3];
//			}
//		}
//	}
//
//	static Matrix Scaling(float target)
//	{
//		Matrix Result;
//		Result.SetIdentity();
//		Result.rc[0][0] = target;
//		Result.rc[1][1] = target;
//		Result.rc[2][2] = target;
//		return Result;
//	}
//	static Matrix Scaling(const Vector3& target)
//	{
//		Matrix Result;
//		Result.SetIdentity();
//		Result.rc[0][0] = target.x;
//		Result.rc[1][1] = target.y;
//		Result.rc[2][2] = target.z;
//		return Result;
//	}
//	static Matrix RotatePitch(float radian)
//	{
//		Matrix Result;
//		Result.SetIdentity();
//		float cos = cosf(radian);
//		float sin = sinf(radian);
//		Result.rc[1][1] = cos; 
//		Result.rc[1][2] = -sin;
//		Result.rc[2][1] = sin; 
//		Result.rc[2][2] = cos;
//		return Result;
//	}
//	static Matrix RotateYaw(float radian)
//	{
//		Matrix Result;
//		Result.SetIdentity();
//		float cos = cosf(radian);
//		float sin = sinf(radian);		
//		Result.rc[0][0] = cos; 
//		Result.rc[0][2] = sin;
//		Result.rc[2][0] = -sin; 
//		Result.rc[2][2] = cos;
//		return Result;
//	}
//	static Matrix RotateRoll(float radian)
//	{
//		Matrix Result;
//		Result.SetIdentity();
//		float cos = cosf(radian);
//		float sin = sinf(radian);
//		Result.rc[0][0] = cos; Result.rc[0][1] = -sin; 
//		Result.rc[1][0] = sin; Result.rc[1][1] = cos; 
//		return Result;
//	}
//	static Matrix Translate(const Vector3& target)
//	{
//		Matrix Result;
//		Result.SetIdentity();
//		Result.rc[0][3] = target.x;
//		Result.rc[1][3] = target.y;
//		Result.rc[2][3] = target.z;
//		Result.rc[3][3] = 1.f;
//		return Result;
//	}
//
//	float& operator[](int index)
//	{
//		return f[index];
//	}
//	float operator[](int index) const
//	{
//		return f[index];
//	}
//	operator DirectX::XMMATRIX()
//	{
//		return DirectX::XMMATRIX(f);
//	}
//	operator DirectX::XMMATRIX() const
//	{
//		return DirectX::XMMATRIX(f);
//	}
//	void operator=(XMMATRIX value)
//	{
//		memcpy(f, value.r, sizeof(float) * 16);
//	}
//};