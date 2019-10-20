/*
Licensed under the MIT License <http://opensource.org/licenses/MIT>.
Copyright (c) 2019 jaefunk <https://github.com/jaefunk/dotth>.

Permission is hereby  granted, free of charge, to any  person obtaining a copy
of this software and associated  documentation files (the "Software"), to deal
in the Software  without restriction, including without  limitation the rights
to  use, copy,  modify, merge,  publish, distribute,  sublicense, and/or  sell
copies  of  the Software,  and  to  permit persons  to  whom  the Software  is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE  IS PROVIDED "AS  IS", WITHOUT WARRANTY  OF ANY KIND,  EXPRESS OR
IMPLIED,  INCLUDING BUT  NOT  LIMITED TO  THE  WARRANTIES OF  MERCHANTABILITY,
FITNESS FOR  A PARTICULAR PURPOSE AND  NONINFRINGEMENT. IN NO EVENT  SHALL THE
AUTHORS  OR COPYRIGHT  HOLDERS  BE  LIABLE FOR  ANY  CLAIM,  DAMAGES OR  OTHER
LIABILITY, WHETHER IN AN ACTION OF  CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE  OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <cstring>
#include "matrix.hpp"

dotth::matrix4::matrix4(void)
{
    memcpy(m, IDENTITY.m, MATRIX_SIZE);
    
}
dotth::matrix4::matrix4(const matrix4& copy)
{
    memcpy(m, copy.m, MATRIX_SIZE);
    
}
dotth::matrix4::matrix4(float _11, float _12, float _13, float _14, float _21, float _22, float _23, float _24, float _31, float _32, float _33, float _34, float _41, float _42, float _43, float _44)
{
    m[0]  = _11; m[4]  = _12; m[8]  = _13; m[12] = _14;
    m[1]  = _21; m[5]  = _22; m[9]  = _23; m[13] = _24;
    m[2]  = _31; m[6]  = _32; m[10] = _33; m[14] = _34;
    m[3]  = _41; m[7]  = _42; m[11] = _43; m[15] = _44;
}

void dotth::matrix4::create_scale(float x, float y, float z, matrix4* dst)
{
    memcpy(dst, &IDENTITY, MATRIX_SIZE);
    dst->m[0] = x; dst->m[5] = y; dst->m[10] = z;
}

void dotth::matrix4::create_translation(float x, float y, float z, matrix4* dst)
{
    memcpy(dst, &IDENTITY, MATRIX_SIZE);
    dst->m[12] = x; dst->m[13] = y; dst->m[14] = z;
}

void dotth::matrix4::multiply(const matrix4& m1, const matrix4& m2, matrix4* dst)
{
    dst->m[0]  = dotth::vector4::dot(m1.row(1), m2.column(1));
    dst->m[1]  = dotth::vector4::dot(m1.row(2), m2.column(1));
    dst->m[2]  = dotth::vector4::dot(m1.row(3), m2.column(1));
    dst->m[3]  = dotth::vector4::dot(m1.row(4), m2.column(1));
    dst->m[4]  = dotth::vector4::dot(m1.row(1), m2.column(2));
    dst->m[5]  = dotth::vector4::dot(m1.row(2), m2.column(2));
    dst->m[6]  = dotth::vector4::dot(m1.row(3), m2.column(2));
    dst->m[7]  = dotth::vector4::dot(m1.row(4), m2.column(2));
    dst->m[8]  = dotth::vector4::dot(m1.row(1), m2.column(3));
    dst->m[9]  = dotth::vector4::dot(m1.row(2), m2.column(3));
    dst->m[10] = dotth::vector4::dot(m1.row(3), m2.column(3));
    dst->m[11] = dotth::vector4::dot(m1.row(4), m2.column(3));
    dst->m[12] = dotth::vector4::dot(m1.row(1), m2.column(4));
    dst->m[13] = dotth::vector4::dot(m1.row(2), m2.column(4));
    dst->m[14] = dotth::vector4::dot(m1.row(3), m2.column(4));
    dst->m[15] = dotth::vector4::dot(m1.row(4), m2.column(4));
}

const dotth::vector4 dotth::matrix4::row(int row) const {
    int target = row - 1;
    return vector4(m[target + 0], m[target + 4], m[target + 8], m[target + 12]);
}
const dotth::vector4 dotth::matrix4::column(int col) const {
    int target = 4 * (col - 1);
    return vector4(m[target + 0], m[target + 1], m[target + 2], m[target + 3]);
}

const dotth::matrix4 dotth::matrix4::ZERO = matrix4(0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f);
const dotth::matrix4 dotth::matrix4::IDENTITY = matrix4(1.f, 0.f, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f, 0.f, 0.f, 1.f);
