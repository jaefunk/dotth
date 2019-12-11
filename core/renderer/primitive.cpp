#include "primitive.hpp"
#include "primitive_command.hpp"

void dotth::rectangle::init(void)
{	
	auto cmd = std::make_shared<dotth::render::command::primitive>();
	cmd->_shader = dotth::shader_manager::instance()->find("ortho");
	cmd->_type = dotth::render::draw_type::orthographic;
	cmd->v = { { -0.5f, 0.5f, 0.f },{ 0.5f, 0.5f, 0.f },{ -0.5f, -0.5f, 0.f },{ 0.5f, -0.5f, 0.f } };
	cmd->c = { {},{},{},{} };
	cmd->i = { 0, 1, 2, 1, 3, 2 };
	_command = cmd;
}

void dotth::rectangle::on_update(const float& delta)
{
	memcpy(_command->_model, trans2d.result(), matrix4::matrix_size);
}

void dotth::rectangle::set_size(const int& width, const int& height)
{
	//trans.scl()
}

void dotth::rectangle::set_anchor(const float& x, const float& y)
{

}

void dotth::rectangle::set_color(const render::rgba & _color)
{
	auto cmd = std::static_pointer_cast<dotth::render::command::primitive>(_command);
	for (auto& c : cmd->c)
		c = _color;
}