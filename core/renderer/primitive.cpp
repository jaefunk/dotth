#include "primitive.hpp"
#include "primitive_command.hpp"

void dotth::rectangle::init(void)
{	
	_trans = std::make_shared<transform2d>(); 
	auto cmd = std::make_shared<dotth::render::command::primitive_orthographic>();
	cmd->_shader = dotth::shader_manager::instance()->find("ortho");
	cmd->_type = dotth::render::draw_type::orthographic;
	cmd->v = { { -0.5f, 0.5f, 0.f },{ 0.5f, 0.5f, 0.f },{ -0.5f, -0.5f, 0.f },{ 0.5f, -0.5f, 0.f } };
	cmd->c = { {},{},{},{} };
	cmd->i = { 0, 1, 2, 1, 3, 2 };
	_command = cmd;
}

void dotth::rectangle::on_update(const float& delta)
{
}

void dotth::rectangle::set_color(const render::rgba & _color)
{
	auto cmd = std::static_pointer_cast<dotth::render::command::primitive_orthographic>(_command);
	for (auto& c : cmd->c)
		c = _color;
}

void dotth::cube::init(void)
{
	_trans = std::make_shared<transform3d>();
	auto cmd = std::make_shared<dotth::render::command::primitive_perspective>();
	cmd->_shader = dotth::shader_manager::instance()->find("mvp");
	cmd->_type = dotth::render::draw_type::perspective;
	cmd->v = { { -0.5f, 0.5f, 0.f },{ 0.5f, 0.5f, 0.f },{ -0.5f, -0.5f, 0.f },{ 0.5f, -0.5f, 0.f } };
	cmd->c = { {},{},{},{} };
	cmd->i = { 0, 1, 2, 1, 3, 2 };
	_command = cmd;
}

void dotth::cube::on_update(const float& delta)
{
}

void dotth::cube::set_color(const render::rgba & _color)
{
	auto cmd = std::static_pointer_cast<dotth::render::command::primitive_perspective>(_command);
	for (auto& c : cmd->c)
		c = _color;
}