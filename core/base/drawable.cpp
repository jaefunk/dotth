#include "drawable.hpp"

dotth::drawable::drawable(const dotth::render::transform_type & _type)
{
	switch (_type)
	{
	case dotth::render::transform_type::perspective:
		_trans = new transform3d;
		break;
	case dotth::render::transform_type::orthographic:
		_trans = new transform2d;
		break;
	default:
		break;
	}
}

dotth::drawable::~drawable(void)
{
	if (_trans != nullptr)
		delete _trans;
	_trans = nullptr;

	if (_command != nullptr)
		delete _command;
	_command = nullptr;
}
