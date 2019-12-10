#ifndef __DOTTH_VECTOR_HPP__
#define __DOTTH_VECTOR_HPP__

#include "dotth.hpp"
#include "math.hpp"

namespace dotth {
	struct vector2 {
		float x, y, z;
		vector2(void);
		vector2(const float& v);
		vector2(const float& x, const float& y);
		vector2(const vector2& v);
		vector2(const vector2&& v);
		const vector2 operator=(const vector2& v) {
			x = v.x; y = v.y;
			return *this;
		}
		const float length(void) const {
			return std::sqrt((x * x) + (y * y));
		}
		const float dot(const vector2& v) const {
			return (x * v.x) + (y * v.y);
		}
		const vector2 add(const vector2& v) const {
			return vector2(x + v.x, y + v.y);
		}
		const vector2 subtract(const vector2& v) const {
			return vector2(x - v.x, y - v.y);
		}
		const vector2 multiply(const float& v) const {
			return vector2(x * v, y * v);
		}
		const vector2 divide(const float& v) const {
			return vector2(x / v, y / v);
		}
		const vector2 negate(void) const {
			return multiply(-1.f);
		}
		const vector2 normalize(void) const {
			float l = length();
			if (l < 0.00001f)
				return vector2(0.f);
			return multiply(1.f / l);
		}
		const char* c_str(void) const;
	};
	struct vector3 {
		float x, y, z;
		vector3(void);
		vector3(const float& v);
		vector3(const float& x, const float& y, const float& z);
		vector3(const vector3& v);
		vector3(const vector3&& v);
		const vector3 operator=(const vector3& v) {
			x = v.x; y = v.y; z = v.z;
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
		const vector3 multiply(const vector3 v) const {
			return vector3(x * v.x, y * v.y, z * v.z);
		}
		const vector3 divide(const float& v) const {
			return vector3(x / v, y / v, z / v);
		}
		const vector3 negate(void) const {
			return multiply(-1.f);
		}
		const vector3 normalize(void) const {
			float l = length();
			if (l < 0.00001f)
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
