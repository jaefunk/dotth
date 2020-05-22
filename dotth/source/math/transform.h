#ifndef __DOTTH_TRANSFORM__
#define __DOTTH_TRANSFORM__

#include "matrix.h"

namespace dotth {
	class transform 
	{
	private:
		bool _sync_ortho = false;
		vector3 _pos = { 0.f, 0.f, 0.f };
		vector3 _scl = { 1.f, 1.f, 1.f };
		vector3 _rot = { 0.f, 0.f, 0.f };
		vector3 _size = { 0.f, 0.f, 0.f };
		vector3 _anchor = { 0.f, 0.f, 0.f };
		matrix4 _matrix;
		matrix4 _matrix_without_scale;
		vector3 _wpos = { 0.f, 0.f, 0.f };
		vector3 _wscl = { 1.f, 1.f, 1.f };
		vector3 _wrot = { 0.f, 0.f, 0.f };

	public: // set
		void set_ortho(bool b) { _sync_ortho = b; }

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

		void size(const float& x, const float& y) { _size.x = x; _size.y = y; }
		void size(const vector2& v) { size(v.x, v.y); }
		void size_x(const float& v) { _size.x = v; }
		void size_y(const float& v) { _size.y = v; }
		void size_z(const float& v) { _size.z = v; }

		void anchor(const float& x, const float& y) { _anchor.x = x; _anchor.y = y; }
		void anchor(const vector2& v) { anchor(v.x, v.y); }
		void anchor_x(const float& v) { _anchor.x = v; }
		void anchor_y(const float& v) { _anchor.y = v; }
		void anchor_z(const float& v) { _anchor.z = v; }

	public: // get
		const vector3& pos(void) const { return _pos; }
		const vector3& scl(void) const { return _scl; }
		const vector3& rot(void) const { return _rot; }
		const vector3& size(void) { return _size; }
		const vector3& anchor(void) { return _anchor; }
		const vector3& wpos(void) const { return _wpos; }
		const vector3& wscl(void) const { return _wscl; }
		const vector3& wrot(void) const { return _wrot; }
		const matrix4& matrix(void) const { return _matrix; }
		const matrix4& matrix_without_scale(void) const { return _matrix_without_scale; }
		const float* result(void) const { return _matrix.m; }
		const bool sync(const transform* parent);
	};
};

#endif // __DOTTH_TRANSFORM__
