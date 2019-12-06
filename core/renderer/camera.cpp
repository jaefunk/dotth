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
    sync_view(); sync_pers(); sync_ortho();
	_dirty_view = _dirty_pers = _dirty_ortho = true;
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

#ifdef VIEW_MATRIX_X_INVERSE
	matrix4 matrix_x_inverse;
	matrix4::scale(matrix_x_inverse, { -1.f, 1.f, 1.f });
	matrix4::multiply(_view, matrix_x_inverse, _view);
#endif
}

void dotth::camera::sync_pers(void) {
	if (_dirty_pers == false)
		return;
	float ar = _width / _height;
	float range = _pers_near - _pers_far;
	float tan = tanf(deg_to_rad(_fov) / 2.f);
	float _11 = 1.f / (tan * ar);
	float _22 = 1.f / tan;
	float _33 = -(-_pers_near - _pers_far) / range;
	float _34 = 2.f * _pers_far * _pers_near / range;
	float _43 = -1.f;
	_pers = matrix4(
		_11, 0.f, 0.f, 0.f, 
		0.f, _22, 0.f, 0.f, 
		0.f, 0.f, _33, _34, 
		0.f, 0.f, _43, 0.f);
}

const float * dotth::camera::ortho(void)
{
	return _ortho.m;
}

void dotth::camera::sync_ortho(void)
{
	if (_dirty_ortho == false)
		return;
	float _11 = 2.f / (_right - _left);
	float _14 = -(_right + _left) / (_right - _left);
	float _22 = 2.f / (_top - _bottom);
	float _24 = -(_top + _bottom) / (_top - _bottom);
	float _33 = -2.f / (_ortho_far - _ortho_near);
	float _34 = -(_ortho_far + _ortho_near) / (_ortho_far - _ortho_near);
	float _44 = 1.f;
	_ortho = matrix4(
		_11, 0.f, 0.f, _14,
		0.f, _22, 0.f, _24,
		0.f, 0.f, _33, _34,
		0.f, 0.f, 0.f, _44);
}
