#include "matrix.hpp"
#include "math.hpp"
#include "base/utility.hpp"

dotth::matrix4::matrix4(void)
{
    memcpy(m, dotth::matrix4::identity.m, dotth::matrix4::matrix_size);
}

dotth::matrix4::matrix4(const matrix4& copy)
{
    memcpy(m, copy.m, dotth::matrix4::matrix_size);
}

dotth::matrix4::matrix4(float _11, float _12, float _13, float _14, float _21, float _22, float _23, float _24, float _31, float _32, float _33, float _34, float _41, float _42, float _43, float _44)
{
    m[0]  = _11; m[4]  = _12; m[8]  = _13; m[12] = _14;
    m[1]  = _21; m[5]  = _22; m[9]  = _23; m[13] = _24;
    m[2]  = _31; m[6]  = _32; m[10] = _33; m[14] = _34;
    m[3]  = _41; m[7]  = _42; m[11] = _43; m[15] = _44;
}

void dotth::matrix4::scale(matrix4 & dst, const vector3 & value)
{
	dst.m[0] = value.x;
	dst.m[5] = value.y;
	dst.m[10] = value.z;
}

void dotth::matrix4::rotate(matrix4 & dst, const vector3 & value)
{
	float sx = sin(deg_to_rad(value.x));
	float cx = cos(deg_to_rad(value.x));
	float sy = sin(deg_to_rad(value.y));
	float cy = cos(deg_to_rad(value.y));
	float sz = sin(deg_to_rad(value.z));
	float cz = cos(deg_to_rad(value.z));

	dst.m[0] = cz * cy;
	dst.m[4] = cz * sy * sx - sz * cy;
	dst.m[8] = cz * sy * cx + sz * sx;
	dst.m[1] = sz * cy;
	dst.m[5] = sz * sy * sx + cz * cx;
	dst.m[9] = sz * sy * cx + cz * sx;
	dst.m[2] = -sy;
	dst.m[6] = cy * sx;
	dst.m[10] = cy * cx;
}

void dotth::matrix4::position(matrix4 & dst, const vector3 & value)
{
	dst.m[12] = value.x;
	dst.m[13] = value.y;
	dst.m[14] = value.z;
}

void dotth::matrix4::multiply(const matrix4 & l, const matrix4 & r, matrix4 & dst)
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

const size_t dotth::matrix4::matrix_size = sizeof(float) * 16;
const dotth::matrix4 dotth::matrix4::identity = matrix4(1.f, 0.f, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f, 0.f, 0.f, 1.f);
const dotth::matrix4 dotth::matrix4::zero = matrix4(0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f);

