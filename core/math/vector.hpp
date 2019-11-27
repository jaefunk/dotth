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
		vector3(void) {}
		vector3(const float& v) : x(v), y(v), z(v) {}
		vector3(const float& x, const float& y, const float& z) : x(x), y(y), z(z) {}
		vector3(const vector3& v) : x(v.x), y(v.y), z(v.z) {}
		vector3(const vector3&& v) : x(v.x), y(v.y), z(v.z) {}
		const float length(void) { return std::sqrt((x * x) + (y * y) + (z * z)); }
		const float dot(const vector3& v) { return (x * v.x) + (y * v.y) + (z * v.z); }
		void add(const vector3& v) { x += v.x; y += v.y; z += v.z; }
		void subtract(const vector3& v) { x -= v.x; y -= v.y; z -= v.z; }
		void multiply(const float& v) { x *= v; y *= v; z *= v; }
		void divide(const float& v) { x /= v; y /= v; z /= v; }
		void negate(void) { multiply(-1.f); }
		const float normalize(void) {
			float l = length(); 
			if (l < FLT_EPSILON) 
				return 0.f;
			multiply(1.f / l); 
			return l;
		}
		const char* c_str(void) {
			return to_string().c_str();
		}
		std::string to_string(void) {
			return utility::string::format("x:%f y:%f z:%f", x, y, z);
		}
	};
};

#endif // __DOTTH_VECTOR_HPP__