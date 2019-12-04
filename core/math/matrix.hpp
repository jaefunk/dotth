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

#ifndef __DOTTH_MATRIX_HPP__
#define __DOTTH_MATRIX_HPP__

#include "vector.hpp"

namespace dotth {
	struct matrix4 {
		float m[16];
        matrix4(void);
        matrix4(const matrix4& copy);
        matrix4(float _11, float _12, float _13, float _14,
                float _21, float _22, float _23, float _24,
                float _31, float _32, float _33, float _34,
                float _41, float _42, float _43, float _44);
		

		static void scale(matrix4& dst, const vector3& value);
		static void rotate(matrix4& dst, const vector3& value);
		static void position(matrix4& dst, const vector3& value);

		static void multiply(matrix4& l, matrix4& r, matrix4& dst)
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
        
		static const size_t matrix_size;
        static const matrix4 identity;
        static const matrix4 zero;
	};
};

#endif // __DOTTH_MATRIX_HPP__
