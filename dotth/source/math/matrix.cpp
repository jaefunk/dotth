#include "matrix.h"
#include <cstring>
#include <cmath>

#define DEGTORAD(x) ((x)*0.0174532925f)

Matrix44::Matrix44(void)
{
    memcpy(m, Matrix44::Identity.m, sizeof(Matrix44));
}

Matrix44::Matrix44(const Matrix44& copy)
{
    memcpy(m, copy.m, sizeof(Matrix44));
}

Matrix44::Matrix44(float _11, float _12, float _13, float _14, float _21, float _22, float _23, float _24, float _31, float _32, float _33, float _34, float _41, float _42, float _43, float _44)
{
    m[0]  = _11; m[4]  = _12; m[8]  = _13; m[12] = _14;
    m[1]  = _21; m[5]  = _22; m[9]  = _23; m[13] = _24;
    m[2]  = _31; m[6]  = _32; m[10] = _33; m[14] = _34;
    m[3]  = _41; m[7]  = _42; m[11] = _43; m[15] = _44;
}

void Matrix44::Copy(const Matrix44 & src, Matrix44 & dst)
{
	memcpy(dst.m, src.m, sizeof(Matrix44));
}

void Matrix44::Scale(Matrix44 & dst, const Float3 & value)
{
	memcpy(dst.m, Matrix44::Identity.m, sizeof(Matrix44));
	dst.m[0] = value.x;
	dst.m[5] = value.y;
	dst.m[10] = value.z;
}


void Matrix44::Rotate(Matrix44 & dst, const Float3 & value)
{
	memcpy(dst.m, Matrix44::Identity.m, sizeof(Matrix44));
	float sx = sin(DEGTORAD(value.x));
	float cx = cos(DEGTORAD(value.x));
	float sy = sin(DEGTORAD(value.y));
	float cy = cos(DEGTORAD(value.y));
	float sz = sin(DEGTORAD(value.z));
	float cz = cos(DEGTORAD(value.z));
	dst.m[0] = cz * cy;
	dst.m[1] = (sz * cx) + (cz * sy * sx);
	dst.m[2] = (sz * sx) - (cz * sy * cx);
	dst.m[4] = -sz * cy;
	dst.m[5] = (cz * cx) - (sz * sy * sx);
	dst.m[6] = (cz * sx) + (sz * sy * cx);
	dst.m[8] = sy;
	dst.m[9] = -cy * sx;
	dst.m[10] = cy * cx;
}

void Matrix44::Translate(Matrix44 & dst, const Float3 & value)
{
	memcpy(dst.m, Matrix44::Identity.m, sizeof(Matrix44));
	dst.m[12] = value.x;
	dst.m[13] = value.y;
	dst.m[14] = value.z;
}

void Matrix44::Multiply(const Matrix44 & l, const Matrix44 & r, Matrix44 & dst)
{
	dst.m[0] = r.m[0] * l.m[0] + r.m[4] * l.m[1] + r.m[8] * l.m[2] + r.m[12] * l.m[3];
	dst.m[1] = r.m[1] * l.m[0] + r.m[5] * l.m[1] + r.m[9] * l.m[2] + r.m[13] * l.m[3];
	dst.m[2] = r.m[2] * l.m[0] + r.m[6] * l.m[1] + r.m[10] * l.m[2] + r.m[14] * l.m[3];
	dst.m[3] = r.m[3] * l.m[0] + r.m[7] * l.m[1] + r.m[11] * l.m[2] + r.m[15] * l.m[3];
	dst.m[4] = r.m[0] * l.m[4] + r.m[4] * l.m[5] + r.m[8] * l.m[6] + r.m[12] * l.m[7];
	dst.m[5] = r.m[1] * l.m[4] + r.m[5] * l.m[5] + r.m[9] * l.m[6] + r.m[13] * l.m[7];
	dst.m[6] = r.m[2] * l.m[4] + r.m[6] * l.m[5] + r.m[10] * l.m[6] + r.m[14] * l.m[7];
	dst.m[7] = r.m[3] * l.m[4] + r.m[7] * l.m[5] + r.m[11] * l.m[6] + r.m[15] * l.m[7];
	dst.m[8] = r.m[0] * l.m[8] + r.m[4] * l.m[9] + r.m[8] * l.m[10] + r.m[12] * l.m[11];
	dst.m[9] = r.m[1] * l.m[8] + r.m[5] * l.m[9] + r.m[9] * l.m[10] + r.m[13] * l.m[11];
	dst.m[10] = r.m[2] * l.m[8] + r.m[6] * l.m[9] + r.m[10] * l.m[10] + r.m[14] * l.m[11];
	dst.m[11] = r.m[3] * l.m[8] + r.m[7] * l.m[9] + r.m[11] * l.m[10] + r.m[15] * l.m[11];
	dst.m[12] = r.m[0] * l.m[12] + r.m[4] * l.m[13] + r.m[8] * l.m[14] + r.m[12] * l.m[15];
	dst.m[13] = r.m[1] * l.m[12] + r.m[5] * l.m[13] + r.m[9] * l.m[14] + r.m[13] * l.m[15];
	dst.m[14] = r.m[2] * l.m[12] + r.m[6] * l.m[13] + r.m[10] * l.m[14] + r.m[14] * l.m[15];
	dst.m[15] = r.m[3] * l.m[12] + r.m[7] * l.m[13] + r.m[11] * l.m[14] + r.m[15] * l.m[15];
}

const Matrix44 Matrix44::Identity = Matrix44(1.f, 0.f, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f, 0.f, 0.f, 1.f);
const Matrix44 Matrix44::Zero = Matrix44(0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f);

