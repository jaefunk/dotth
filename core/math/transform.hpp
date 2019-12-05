#ifndef __DOTTH_TRANSFORM_HPP__
#define __DOTTH_TRANSFORM_HPP__

#include "matrix.hpp"

namespace dotth {
    class transform {
    private:
		vector3 _pos = { 0.f, 0.f, 0.f };
		vector3 _scl = { 1.f, 1.f, 1.f };
        vector3 _rot = { 0.f, 0.f, 0.f };
        matrix4 _matrix;
    
    public: // set
		void pos(const float& x, const float& y, const float& z) { _pos.x = x; _pos.y = y; _pos.z = z; }
        void pos(const vector3& v) { pos(v.x, v.y, v.z); }
		void pos_x(const float& v) { _pos.x = v; }
		void pos_y(const float& v) { _pos.y = v; }
		void pos_z(const float& v) { _pos.z = v; }
		
		void scl(const float& x, const float& y, const float& z) { _scl.x = x; _scl.y = y; _scl.z = z; }
		void scl(const vector3& v) { scl(v.x, v.y, v.z); }
		void scl_x(const float& v) { _scl.x = v; }
		void scl_y(const float& v) { _scl.y = v; }
		void scl_z(const float& v) { _scl.z = v; }

		void rot(const float& x, const float& y, const float& z) { _rot.x = x; _rot.y = y; _rot.z = z; }
		void rot(const vector3& v) { rot(v.x, v.y, v.z); }
		void rot_x(const float& v) { _rot.x = v; }
		void rot_y(const float& v) { _rot.y = v; }
		void rot_z(const float& v) { _rot.z = v; }

	public:
		void sync(const matrix4& parent)
		{
			auto matrix_scale = matrix4::identity;
			auto matrix_rotate = matrix4::identity;
			auto matrix_position = matrix4::identity;

			matrix4::scale(matrix_scale, _scl);
			matrix4::rotate(matrix_rotate, _rot);
			matrix4::position(matrix_position, _pos);
			matrix4 scale_rotate;
			matrix4::multiply(matrix_scale, matrix_rotate, scale_rotate);
			matrix4 scale_rotate_position;
			matrix4::multiply(scale_rotate, matrix_position, scale_rotate_position);
			matrix4::multiply(scale_rotate_position, parent, _matrix);
		}
        
    public: // get
        const vector3& pos(void) { return _pos; }
        const vector3& scl(void) { return _scl; }
        const vector3& rot(void) { return _rot; }
        const matrix4& matrix(void) { return _matrix; }
		const float* result(void) { return _matrix.m; }
    };
};

#endif // __DOTTH_TRANSFORM_HPP__
