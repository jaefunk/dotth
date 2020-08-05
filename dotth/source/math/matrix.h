
#include "TypeFloat.h"

struct Matrix44 {
	float m[16];
	Matrix44(void);
	Matrix44(const Matrix44& copy);
	Matrix44(float _11, float _12, float _13, float _14,
		float _21, float _22, float _23, float _24,
		float _31, float _32, float _33, float _34,
		float _41, float _42, float _43, float _44);
	static void Copy(const Matrix44 & src, Matrix44 & dst);
	static void Scale(Matrix44& dst, const Float3& value);
	static void Rotate(Matrix44& dst, const Float3& value);
	static void Translate(Matrix44& dst, const Float3& value);
	static void Multiply(const Matrix44& l, const Matrix44& r, Matrix44& dst);
	
	static const Matrix44 Identity;
	static const Matrix44 Zero;
};