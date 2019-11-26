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

#include "math.hpp"

namespace dotth {
	template <typename ty>
	struct vector3 {
		union { struct { ty x, y, z; }; };
		vector3(void) {}
		vector3(const ty& v) : x(v), y(v), z(v) {}
		vector3(const ty& xx, const ty& yy, const ty& zz) : x(xx), y(yy), z(zz) {}
		vector3(const vector3<ty>& v) : x(v.x), y(v.y), z(v.z) {}
		vector3(const vector3<ty>&& v) : x(v.x), y(v.y), z(v.z) {}
		const ty length(void) { 
			return std::sqrt((x * x) + (y * y) + (z * z)); 
		}
		const ty dot(const vector3<ty>& v) { 
			return (x * v.x) + (y * v.y) + (z * v.z); 
		}
		void add(const vector3<ty>& v) {
			x += v.x;
			y += v.y;
			z += v.z;
		}
		void subtract(const vector3<ty>& v) {
			add(v.negate());
		}
		void multiply(const ty& v) {
			x *= v;
			y *= v;
			z *= v;
		}
		void divide(const ty& v) {
			x /= v;
			y /= v;
			z /= v;
		}
		void negate(void) {
			multiply(-static_cast<ty>(1));
		}
		const ty normalize(void) {
			ty l = length();
			if (l < FLT_EPSILON)
				return static_cast<ty>(0);
			multiply(static_cast<ty>(1) / l);
			return l;
		}
	};
	using vector3i = vector3<int>;
	using vector3f = vector3<float>;
	using vector3d = vector3<double>;
};

#endif // __DOTTH_VECTOR_HPP__