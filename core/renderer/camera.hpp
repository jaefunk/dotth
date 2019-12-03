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

#ifndef __DOTTH_CAMERA_HPP__
#define __DOTTH_CAMERA_HPP__

#include "math/matrix.hpp"

namespace dotth {
	class camera : public utility::singleton<camera> {
	private:
		bool _dirty_view = false;
		bool _dirty_pers = false;
		bool _dirty_orth = false;
		vector3 _eye;
		vector3 _up = vector3(0.f, 1.f, 0.f);
		vector3 _at;
		
		float _near;
		float _far;
		float _fov;
		float _width;
		float _height;

		matrix4 _view;
		matrix4 _pers;
		matrix4 _orth;
		matrix4 _view_pers;
	public:
		const float* view(void);
		void sync_view(void);
		const float* pers(void);
		void sync_pers(void);
		const float* view_pers(void);
		void sync_all(void);		
		
	public:
		void set_view(const vector3& eye, const vector3& up, const vector3& at) {
			set_eye(eye), set_up(up), set_at(at);
		}
		void set_eye(const vector3& v) { _dirty_view = true, _eye = v; }
		void set_up(const vector3& v) { _dirty_view = true, _up = v; }
		void set_at(const vector3& v) { _dirty_view = true, _at = v; }
		
		void set_pers(const float& z_near, const float& z_far, const float& width, const float& height, const float& fov) {
			set_near(z_near), set_far(z_far), set_aspect(width, height), set_fov(fov);
		}
		void set_near(const float& v) { _dirty_pers = true, _near = v; }
		void set_far(const float& v) { _dirty_pers = true, _far = v; }
		void set_aspect(const float& w, const float& h) { _dirty_pers = true, _width = w, _height = h; }
		void set_fov(const float& v) { _dirty_pers = true, _fov = v; }
	};
};

#endif // __DOTTH_CAMERA_HPP__
