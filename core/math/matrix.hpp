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
		

		static void scale(matrix4& dst, const vector3& value)
		{
			dst.m[0] = value.x;
			dst.m[5] = value.y;
			dst.m[10] = value.z;
		}
		static void rotate(matrix4& dst, const vector3& value)
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
		static void position(matrix4& dst, const vector3& value)
		{
			dst.m[3] = value.x;
			dst.m[7] = value.y;
			dst.m[11] = value.z;
		}
        
		static const std::size_t matrix_size;
        static const matrix4 identity;
        static const matrix4 zero;
	};
};

#endif // __DOTTH_MATRIX_HPP__
