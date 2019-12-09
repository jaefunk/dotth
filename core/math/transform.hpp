#ifndef __DOTTH_TRANSFORM_HPP__
#define __DOTTH_TRANSFORM_HPP__

#include "matrix.hpp"

namespace dotth {
    class transform {
    private:
		bool _ortho = false;
		vector3 _pos = { 0.f, 0.f, 0.f };
		vector3 _scl = { 1.f, 1.f, 1.f };
        vector3 _rot = { 0.f, 0.f, 0.f };
		vector2 _size = { 0.f, 0.f };
		vector2 _anchor = { 0.f, 0.f };
        matrix4 _matrix;
    
    public: // set
		void set_ortho(const bool& is_ortho) { _ortho = is_ortho; }

		void pos(const float& x, const float& y, const float& z = 0.f) { _pos.x = x; _pos.y = y; _pos.z = z; }
        void pos(const vector3& v) { pos(v.x, v.y, v.z); }
		void pos_x(const float& v) { _pos.x = v; }
		void pos_y(const float& v) { _pos.y = v; }
		void pos_z(const float& v) { _pos.z = v; }
		
		void scl(const float& x, const float& y, const float& z = 1.f) { _scl.x = x; _scl.y = y; _scl.z = z; }
		void scl(const vector3& v) { scl(v.x, v.y, v.z); }
		void scl_x(const float& v) { _scl.x = v; }
		void scl_y(const float& v) { _scl.y = v; }
		void scl_z(const float& v) { _scl.z = v; }

		void rot(const float& x, const float& y, const float& z) { _rot.x = x; _rot.y = y; _rot.z = z; }
		void rot(const vector3& v) { rot(v.x, v.y, v.z); }
		void rot_x(const float& v) { _rot.x = v; }
		void rot_y(const float& v) { _rot.y = v; }
		void rot_z(const float& v) { _rot.z = v; }

		void size(const float& w, const float& h) { _size.x = w; _size.y = h; }
		void size(const vector2& v) { size(v.x, v.y); }
		void size_x(const float& v) { _size.x = v; }
		void size_y(const float& v) { _size.y = v; }

		void anchor(const float& w, const float& h) { _anchor.x = w; _anchor.y = h; }
		void anchor(const vector2& v) { anchor(v.x, v.y); }
		void anchor_x(const float& v) { _anchor.x = v; }
		void anchor_y(const float& v) { _anchor.y = v; }

	public:
		void sync(const transform& parent);
        
    public: // get
        const vector3& pos(void) { return _pos; }
        const vector3& scl(void) { return _scl; }
        const vector3& rot(void) { return _rot; }
		const vector2& size(void) { return _size; }
		const vector2& anchor(void) { return _anchor; }
        const matrix4& matrix(void) { return _matrix; }
		const float* result(void) { return _matrix.m; }
    };
};

#endif // __DOTTH_TRANSFORM_HPP__
