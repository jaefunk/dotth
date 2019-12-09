#ifndef __DOTTH_CAMERA_HPP__
#define __DOTTH_CAMERA_HPP__

#include "math/matrix.hpp"

#define VIEW_MATRIX_X_INVERSE

namespace dotth {
	class camera : public utility::singleton<camera> {
	private:
		bool _dirty_view = false;
		bool _dirty_pers = false;
		bool _dirty_ortho = false;
		vector3 _eye;
		vector3 _up = vector3(0.f, 1.f, 0.f);
		vector3 _at;
		
		float _pers_near;
		float _pers_far;
		float _fov;
		float _width;
		float _height;

		float _ortho_near;
		float _ortho_far;
		float _left;
		float _top;
		float _right;
		float _bottom;

		float _ortho1px;

		matrix4 _view;
		matrix4 _pers;
		matrix4 _ortho;
		matrix4 _view_pers;
	public:
		const float* view(void);
		void sync_view(void);
		const float* pers(void);
		void sync_pers(void);
		const float* ortho(void);
		const float& ortho1px(void);
		void sync_ortho(void);
		const float* view_pers(void);
		void sync_all(void);
		
	public:
		void set_view(const vector3& eye, const vector3& up, const vector3& at) {
            set_eye(eye); set_up(up); set_at(at);
		}
        void set_eye(const vector3& v) { _dirty_view = true; _eye = v; }
        void set_up(const vector3& v) { _dirty_view = true; _up = v; }
        void set_at(const vector3& v) { _dirty_view = true; _at = v; }
		
		void set_pers(const float& z_near, const float& z_far, const float& width, const float& height, const float& fov) {
            set_pers_near(z_near); set_pers_far(z_far); set_aspect(width, height); set_fov(fov);
		}
		
        void set_pers_near(const float& v) { _dirty_pers = true; _pers_near = v; }
        void set_pers_far(const float& v) { _dirty_pers = true; _pers_far = v; }
        void set_aspect(const float& w, const float& h) { _dirty_pers = true; _width = w; _height = h; }
        void set_fov(const float& v) { _dirty_pers = true; _fov = v; }

		void set_ortho(const float& z_near, const float& z_far, const float& left, const float& top, const float& right, const float& bottom) {
            set_ortho_near(z_near); set_ortho_far(z_far); set_ltrb(left, top, right, bottom);
		}
        void set_ortho_near(const float& v) { _dirty_ortho = true; _ortho_near = v; }
        void set_ortho_far(const float& v) { _dirty_ortho = true; _ortho_far = v; }
        void set_ltrb(const float& l, const float& t, const float& r, const float& b) { _dirty_ortho = true; _left = l; _top = t; _right = r; _bottom = b; }
		void set_ortho1px(const float& _1px) { _ortho1px = _1px; }
	};
};

#endif // __DOTTH_CAMERA_HPP__
