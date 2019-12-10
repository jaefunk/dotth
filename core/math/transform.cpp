#include "transform.hpp"
#include "renderer/camera.hpp"

void dotth::transform::sync(const transform & parent)
{
	if (_ortho)
	{
		float px = camera::instance()->ortho1px();
		
		auto size = _size.multiply(_scl);
		size = size.multiply(parent._scl);
		auto scl = size.multiply(px);
		
		//_scl = { s.x / parent._scl.x, s.y / parent._scl.y, 1.f };
		
		vector3 p = _pos.multiply(px);
		p = p.multiply(parent._scl);
		_scl = _scl.multiply(parent._scl);
		//p = { p.x / parent._scl.x, p.y / parent._scl.y, 0.f };

		matrix4 matrix_scale;
		matrix4::scale(matrix_scale, scl);

		matrix4 matrix_rotate;
		matrix4::rotate(matrix_rotate, _rot);

		matrix4 matrix_position;
		matrix4::position(matrix_position, p);

		matrix4 scale_rotate;
		matrix4::multiply(matrix_scale, matrix_rotate, scale_rotate);
		
		matrix4 scale_rotate_position;
		matrix4::multiply(scale_rotate, matrix_position, scale_rotate_position);

		matrix4::multiply(scale_rotate_position, parent._matrix_without_scale, _matrix);

		matrix4::multiply(matrix_rotate, matrix_position, _matrix_without_scale);
		matrix4::multiply(_matrix_without_scale, parent._matrix_without_scale, _matrix_without_scale);
	}
	else
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
}
