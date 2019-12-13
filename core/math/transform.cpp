#include "transform.hpp"
#include "renderer/camera.hpp"

void dotth::transform2d::sync(const transform* parent)
{
	float const& _1px = camera::instance()->ortho1px();
	_size = { 100.f, 100.f };
	
    _wscl = parent != nullptr ? _scl.multiply(parent->wscl()) : _scl;
    
	vector3 _tmp_scale = _size;
    _tmp_scale = _tmp_scale.multiply(_wscl);
	_tmp_scale = _tmp_scale.multiply(_1px);
    matrix4 matrix_scale;
    matrix4::scale(matrix_scale, _tmp_scale);
    
	matrix4 matrix_rotate;
	matrix4::rotate(matrix_rotate, _rot);

    vector3 _tmp_pos = _pos.multiply(_wscl);
    _tmp_pos = _tmp_pos.multiply(_1px);
	matrix4 matrix_position;
	matrix4::position(matrix_position, _tmp_pos);

	matrix4 scale_rotate;
	matrix4::multiply(matrix_scale, matrix_rotate, scale_rotate);

	matrix4 scale_rotate_position;
	matrix4::multiply(scale_rotate, matrix_position, scale_rotate_position);
	
	if (parent == nullptr)
		matrix4::copy(_matrix, scale_rotate_position);
	else
		matrix4::multiply(scale_rotate_position, parent->matrix_without_scale(), _matrix);

	matrix4::multiply(matrix_rotate, matrix_position, _matrix_without_scale);
	if (parent != nullptr)
		matrix4::multiply(_matrix_without_scale, parent->matrix_without_scale(), _matrix_without_scale);

}

void dotth::transform3d::sync(const transform* parent)
{
	matrix4 matrix_scale;
	matrix4::scale(matrix_scale, _scl);

	matrix4 matrix_rotate;
	matrix4::rotate(matrix_rotate, _rot);

	matrix4 matrix_position;
	matrix4::position(matrix_position, _pos);

	matrix4 scale_rotate;
	matrix4::multiply(matrix_scale, matrix_rotate, scale_rotate);

	matrix4 scale_rotate_position;
	matrix4::multiply(scale_rotate, matrix_position, scale_rotate_position);
	
	if (parent == nullptr)
		_matrix = scale_rotate_position;
	else
		matrix4::multiply(scale_rotate_position, parent->matrix(), _matrix);
}
