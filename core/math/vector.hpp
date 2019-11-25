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
	struct vector4 {
		union { struct { ty x, y, z, w; }; struct { ty r, g, b, a; }; };
		vector4(const ty& v) : x(v), y(v), z(v), w(v) {};
		vector4(const ty& xx, const ty& yy, const ty& zz, const ty& ww) : x(xx), y(yy), z(zz), w(ww) {};
		vector4(const vector4<ty>& v) : x(v.x), y(v.y), z(v.z), w(v.w) {};
		vector4(const vector4<ty>&& v) : x(v.x), y(v.y), z(v.z), w(v.w) {};
		const float length(void) { return std::sqrt((x * x) + (y * y) + (z * z) + (w * w)); }
		const float dot(const vector4<ty>& v) { return (x * v.x) + (y * v.y) + (z * v.z) + (w * v.w); };
		
		template <typename ty = float>
		const bool is_zero(void) { return x == 0.f && y == 0.f && z == 0.f && w == 0.f; }
		template <typename ty = int>
		const bool is_zero(void) { return x == 0 && y == 0 && z == 0 && w == 0; }
		template <typename ty = double>
		const bool is_zero(void) { return x == 0.0 && y == 0.0 && z == 0.0 && w == 0.0; }

		const float distance(const vector4<ty>& v) { ty dx = v.x - x; ty dy = v.y - y; ty dz = v.z - z; ty dw = v.w - w; return std::sqrt(dx * dx + dy * dy + dz * dz + dw * dw); }
	};
};

#endif // __DOTTH_VECTOR_HPP__