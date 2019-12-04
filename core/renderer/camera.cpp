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

#include "camera.hpp"
#include "math/math.hpp"

const float * dotth::camera::view(void) {
	//glGetFloatv(GL_MODELVIEW_MATRIX, _view.m);
	return _view.m;
}

const float * dotth::camera::pers(void) {
	//glGetFloatv(GL_PROJECTION_MATRIX, _proj.m);
	return _pers.m;
}

const float * dotth::camera::view_pers(void) {
	return _view_pers.m;
}

void dotth::camera::sync_all(void)
{
	sync_view(), sync_pers();
	_dirty_view = _dirty_pers = true;
	matrix4::multiply(_view, _pers, _view_pers);
}

void dotth::camera::sync_view(void) {
	if (_dirty_view == false)
		return;
	vector3 axis_z = _eye.subtract(_at).normalize();
	vector3 axis_x = _up.cross(axis_z).normalize();
	vector3 axis_y = axis_z.cross(axis_x);
	_view.m[0] = axis_x.x;
	_view.m[4] = axis_x.y;
	_view.m[8] = axis_x.z;

	_view.m[1] = axis_y.x;
	_view.m[5] = axis_y.y;
	_view.m[9] = axis_y.z;

	_view.m[2] = axis_z.x;
	_view.m[6] = axis_z.y;
	_view.m[10] = axis_z.z;

	_view.m[3] = 0.f;
	_view.m[7] = 0.f;
	_view.m[11] = 0.f;

	_view.m[12] = -axis_x.dot(_eye);
	_view.m[13] = -axis_y.dot(_eye);
	_view.m[14] = -axis_z.dot(_eye);
	_view.m[15] = 1.f;
}

void dotth::camera::sync_pers(void) {
	if (_dirty_pers == false)
		return;
	float ar = _width / _height;
	float range = _near - _far;
	float tan = tanf(deg_to_rad(_fov) / 2.f);
	float _00 = 1.f / (tan * ar);
	float _11 = 1.f / tan;
	float _22 = -(-_near - _far) / range;
	float _23 = 2.f * _far * _near / range;
	float _32 = -1.f;
	_pers = matrix4(
		_00, 0.f, 0.f, 0.f, 
		0.f, _11, 0.f, 0.f, 
		0.f, 0.f, _22, _23, 
		0.f, 0.f, _32, 0.f);
}
