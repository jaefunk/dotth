#include "transform.hpp"
#include "renderer/camera.hpp"

void dotth::transform2d::sync(const transform2d & parent)
{
	float const& _1px = camera::instance()->ortho1px();

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

	matrix4::multiply(scale_rotate_position, parent._matrix, _matrix);
}

void dotth::transform3d::sync(const transform3d & parent)
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

	matrix4::multiply(scale_rotate_position, parent._matrix, _matrix);
}