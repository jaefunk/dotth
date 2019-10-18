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
	struct vector4 {
		union { struct { float x, y, z, w; }; struct { float r, g, b, a; }; };
		vector4(const float& v) : x(v), y(v), z(v), w(v) {};
		vector4(const float& xx = 0.f, const float& yy = 0.f, const float& zz = 0.f, const float& ww = 0.f) : x(xx), y(yy), z(zz), w(ww) {};
		vector4(const vector4& v) : x(v.x), y(v.y), z(v.z), w(v.w) {};
		vector4(const vector4&& v) : x(v.x), y(v.y), z(v.z), w(v.w) {};
		static void clamp(const vector4& v, const vector4& min, const vector4& max, vector4* dst)
		{
			dst->x = v.x; dst->y = v.y; dst->z = v.z; dst->w = v.w;
			if (dst->x < min.x) dst->x = min.x;
			if (dst->x > max.x) dst->x = max.x;
			if (dst->y < min.y) dst->y = min.y;
			if (dst->y > max.y) dst->y = max.y;
			if (dst->z < min.z) dst->z = min.z;
			if (dst->z > max.z) dst->z = max.z;
			if (dst->w < min.w) dst->w = min.w;
			if (dst->w > max.w) dst->w = max.w;
		}
		static void add(const vector4& v1, const vector4& v2, vector4* dst)
		{
			dst->x = v1.x + v2.x;
			dst->y = v1.y + v2.y;
			dst->z = v1.z + v2.z;
			dst->w = v1.w + v2.w;
		}
		static float dot(const vector4& v1, const vector4& v2)
		{
			return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w);
		}
		static float angle(const vector4& v1, const vector4& v2)
		{
			float dx = v1.w * v2.x - v1.x * v2.w - v1.y * v2.z + v1.z * v2.y;
			float dy = v1.w * v2.y - v1.y * v2.w - v1.z * v2.x + v1.x * v2.z;
			float dz = v1.w * v2.z - v1.z * v2.w - v1.x * v2.y + v1.y * v2.x;
			return std::atan2(std::sqrt(dx * dx + dy * dy + dz * dz), dot(v1, v2));
		}
		static void subtract(const vector4& v1, const vector4& v2, vector4* dst)
		{
			dst->x = v1.x - v2.x;
			dst->y = v1.y - v2.y;
			dst->z = v1.z - v2.z;
			dst->w = v1.w - v2.w;
		}
		void normalize(void) 
		{
			float n = x * x + y * y + z * z + w * w;
			if (n == 1.0f) return;
			n = std::sqrt(n);
			if (n < MATH_TOLERANCE) return;
			n = 1.0f / n; x *= n; y *= n; z *= n; w *= n;
		}
		const float length(void) { return std::sqrt((x * x) + (y * y) + (z * z) + (w * w)); }
		const float dot(const vector4& v) { return (x * v.x) + (y * v.y) + (z * v.z) + (w * v.w); };
		const bool zero(void) { return x == 0.f && y == 0.f && z == 0.f && w == 0.f; }
		const bool one(void) { return x == 1.f && y == 1.f && z == 1.f && w == 1.f; }
		const float distance(const vector4& v) { float dx = v.x - x; float dy = v.y - y; float dz = v.z - z; float dw = v.w - w; return std::sqrt(dx * dx + dy * dy + dz * dz + dw * dw); }
	};
};

#endif // __DOTTH_VECTOR_HPP__