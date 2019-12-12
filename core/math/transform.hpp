#ifndef __DOTTH_TRANSFORM_HPP__
#define __DOTTH_TRANSFORM_HPP__

#include "matrix.hpp"

namespace dotth {
	class transform {
	protected:
		vector3 _pos = { 0.f, 0.f, 0.f };
		vector3 _scl = { 1.f, 1.f, 1.f };
		vector3 _rot = { 0.f, 0.f, 0.f };
		matrix4 _matrix;
		matrix4 _matrix_without_scale;
	public:
		virtual void sync(const transform* parent) = 0;

	public: // set
		void pos(const float& x, const float& y, const float& z) { _pos.x = x; _pos.y = y; _pos.z = z; }
		void scl(const float& x, const float& y, const float& z) { _scl.x = x; _scl.y = y; _scl.z = z; }
		void rot(const float& x, const float& y, const float& z) { _rot.x = x; _rot.y = y; _rot.z = z; }

	public: // get
		const vector3& pos(void) const { return _pos; }
		const vector3& scl(void) const { return _scl; }
		const vector3& rot(void) const { return _rot; }
		const matrix4& matrix(void) const { return _matrix; }
		const matrix4& matrix_without_scale(void) const { return _matrix_without_scale; }
		const float* result(void) const { return _matrix.m; }
	};

	class transform2d : public transform {
	private:
		vector2 _size = { 0.f, 0.f };		
		vector2 _anchor = { 0.f, 0.f };	

	public: // set
		void pos(const vector3& v) { transform::pos(v.x, v.y, v.z); }
		void pos_x(const float& v) { _pos.x = v; }
		void pos_y(const float& v) { _pos.y = v; }
		void pos_z(const float& v) { _pos.z = v; }

		void scl(const vector3& v) { transform::scl(v.x, v.y, v.z); }
		void scl_x(const float& v) { _scl.x = v; }
		void scl_y(const float& v) { _scl.y = v; }
		void scl_z(const float& v) { _scl.z = v; }

		void rot(const vector3& v) { transform::rot(v.x, v.y, v.z); }
		void rot_x(const float& v) { _rot.x = v; }
		void rot_y(const float& v) { _rot.y = v; }
		void rot_z(const float& v) { _rot.z = v; }

		void size(const float& x, const float& y) { _size.x = x; _size.y = y; }
		void size(const vector2& v) { size(v.x, v.y); }
		void size_x(const float& v) { _size.x = v; }
		void size_y(const float& v) { _size.y = v; }

		void anchor(const float& x, const float& y) { _anchor.x = x; _anchor.y = y; }
		void anchor(const vector2& v) { anchor(v.x, v.y); }
		void anchor_x(const float& v) { _anchor.x = v; }
		void anchor_y(const float& v) { _anchor.y = v; }

	public:
		virtual void sync(const transform* parent) override;

	public: // get
		const vector2& anchor(void) { return _anchor; }
	};

    class transform3d : public transform {
    public: // set

        void pos(const vector3& v) { transform::pos(v.x, v.y, v.z); }
		void pos_x(const float& v) { _pos.x = v; }
		void pos_y(const float& v) { _pos.y = v; }
		void pos_z(const float& v) { _pos.z = v; }
		
		
		void scl(const vector3& v) { transform::scl(v.x, v.y, v.z); }
		void scl_x(const float& v) { _scl.x = v; }
		void scl_y(const float& v) { _scl.y = v; }
		void scl_z(const float& v) { _scl.z = v; }

		
		void rot(const vector3& v) { transform::rot(v.x, v.y, v.z); }
		void rot_x(const float& v) { _rot.x = v; }
		void rot_y(const float& v) { _rot.y = v; }
		void rot_z(const float& v) { _rot.z = v; }
	
	public:
		virtual void sync(const transform* parent) override;
    };
};

#endif // __DOTTH_TRANSFORM_HPP__
