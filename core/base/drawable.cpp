#include "drawable.hpp"

dotth::drawable::drawable(const dotth::render::transform_type & _type)
{
	switch (_type)
	{
	case dotth::render::transform_type::perspective:
		break;
	case dotth::render::transform_type::orthographic:
		_trans.set_ortho(true);
		break;
	default:
		break;
	}
}

dotth::drawable::~drawable(void)
{
	if (_command != nullptr)
		delete _command;
	_command = nullptr;
}
