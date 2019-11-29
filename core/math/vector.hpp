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

#ifndef __DOTTH_VECTOR_HPP__
#define __DOTTH_VECTOR_HPP__

#include "dotth.hpp"

namespace dotth {
	struct vector3 {
		float x, y, z;
		vector3(void);
		vector3(const float& v);
		vector3(const float& x, const float& y, const float& z);
		vector3(const vector3& v);
		vector3(const vector3&& v);
		const vector3 operator=(const vector3& v) {
			x = v.x, y = v.y, z = v.z;
			return *this;
		}
		const float length(void) const {
			return std::sqrt((x * x) + (y * y) + (z * z));
		}
		const float dot(const vector3& v) const {
			return (x * v.x) + (y * v.y) + (z * v.z);
		}
		const vector3 add(const vector3& v) const {
			return vector3(x + v.x, y + v.y, z + v.z);
		}
		const vector3 subtract(const vector3& v) const {
			return vector3(x - v.x, y - v.y, z - v.z);
		}
		const vector3 multiply(const float& v) const {
			return vector3(x * v, y * v, z * v);
		}
		const vector3 divide(const float& v) const {
			return vector3(x / v, y / v, z / v);
		}
		const vector3 negate(void) const {
			return multiply(-1.f);
		}
		const vector3 normalize(void) const {
			float l = length();
			if (l < FLT_EPSILON)
				return vector3(0.f);
			return multiply(1.f / l);
		}
		const vector3 cross(const vector3& v) const
		{
			return vector3((y * v.z) - (z * v.y), (z * v.x) - (x * v.z), (x * v.y) - (y * v.x));
		}
		const char* c_str(void) const;
	};
};

#endif // __DOTTH_VECTOR_HPP__