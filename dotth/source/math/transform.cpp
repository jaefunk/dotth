#include "transform.h"

const bool dotth::transform::sync(const transform* parent)
{
	static matrix4 matrix_scale, matrix_position, matrix_rotate, scale_rotate, scale_rotate_position, rotate_position;
	static vector3  _tmp_scale, _tmp_pos;	
	if (_sync_ortho)
	{
		float const& _1px = 1.f;
		_wscl = parent != nullptr ? _scl.multiply(parent->wscl()) : _scl;
		_tmp_scale = vector3(_size).multiply(_wscl).multiply(_1px);
		_tmp_pos = _pos.multiply(_wscl).multiply(_1px);
		matrix4::scale(matrix_scale, _tmp_scale);
		matrix4::rotate(matrix_rotate, _rot);
		matrix4::position(matrix_position, _tmp_pos);
		matrix4::multiply(matrix_scale, matrix_rotate, scale_rotate);
		matrix4::multiply(scale_rotate, matrix_position, scale_rotate_position);
		if (parent == nullptr)
			matrix4::copy(scale_rotate_position, _matrix);
		else
			matrix4::multiply(scale_rotate_position, parent->matrix_without_scale(), _matrix);
		matrix4::multiply(matrix_rotate, matrix_position, rotate_position);
		if (parent == nullptr)
			matrix4::copy(rotate_position, _matrix_without_scale);
		else
			matrix4::multiply(rotate_position, parent->matrix_without_scale(), _matrix_without_scale);
	}
	else
	{
		matrix4::scale(matrix_scale, _scl);
		matrix4::rotate(matrix_rotate, _rot);
		matrix4::position(matrix_position, _pos);
		matrix4::multiply(matrix_scale, matrix_rotate, scale_rotate);
		matrix4::multiply(scale_rotate, matrix_position, scale_rotate_position);
		if (parent == nullptr)
			matrix4::copy(scale_rotate_position, _matrix);
		else
			matrix4::multiply(scale_rotate_position, parent->matrix(), _matrix);
	}
	return true;
}
