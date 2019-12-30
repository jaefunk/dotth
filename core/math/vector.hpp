#ifndef __DOTTH_VECTOR_HPP__
#define __DOTTH_VECTOR_HPP__

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
		const float length(void) const;
		const float dot(const vector2& v) const;
		const vector2 add(const vector2& v) const;
		const vector2 subtract(const vector2& v) const;
		const vector2 multiply(const float& v) const;
		const vector2 divide(const float& v) const;
		const vector2 negate(void) const;
		const vector2 normalize(void) const;
		const char* c_str(void) const;
	};
	struct vector3 {
		float x, y, z;
		vector3(void);
		vector3(const float& v);
		vector3(const float& x, const float& y, const float& z);
		vector3(const vector2& v);
		vector3(const vector2&& v);
		vector3(const vector3& v);
		vector3(const vector3&& v);
		const vector3 operator=(const vector2& v) {
			x = v.x; y = v.y; z = 0.f;
			return *this;
		}
		const vector3 operator=(const vector3& v) {
			x = v.x; y = v.y; z = v.z;
			return *this;
		}
		const float length(void) const;
		const float dot(const vector3& v) const;
		const vector3 add(const vector3& v) const;
		const vector3 subtract(const vector3& v) const;
		const vector3 multiply(const float& v) const;
		const vector3 multiply(const vector3 v) const;
		const vector3 divide(const float& v) const;
		const vector3 negate(void) const;
		const vector3 normalize(void) const;
		const vector3 cross(const vector3& v) const;
		const char* c_str(void) const;
	};

	struct vector4 : public vector3 {
		float w;
		vector4(void) 
		{
			w = 0.f;
		}
		vector4(const float& v) : vector3(v) 
		{
			w = v;
		}
		vector4(const float& x, const float& y, const float& z, const float& w) : vector3(x, y, z)
		{
			this->w = w;
		}
		vector4(const vector3& v) : vector3(v)
		{
			w = 0.f;
		}
		vector4(const vector3&& v) : vector3(v)
		{
			w = 0.f;
		}
	};

	typedef vector2 float2;
	typedef vector3 float3;
	typedef vector4 float4;
};

#endif // __DOTTH_VECTOR_HPP__
