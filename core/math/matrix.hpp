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
		static void copy(const matrix4 & src, matrix4 & dst);
		static void scale(matrix4& dst, const vector3& value);
		static void rotate(matrix4& dst, const vector3& value);
		static void position(matrix4& dst, const vector3& value);
		static void multiply(const matrix4& l, const matrix4& r, matrix4& dst);
		static const size_t matrix_size;
        static const matrix4 identity;
        static const matrix4 zero;
	};
};

#endif // __DOTTH_MATRIX_HPP__
