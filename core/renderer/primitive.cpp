#include "primitive.hpp"
#include "primitive_command.hpp"

void dotth::rectangle::init(void)
{	
	assign_command<primitive_orthographic>();
	command<primitive_orthographic>()->_shader = dotth::shader_manager::instance()->find("ortho");
	command<primitive_orthographic>()->_type = dotth::render::draw_type::orthographic;
	command<primitive_orthographic>()->v = { { -0.5f, 0.5f, 0.f },{ 0.5f, 0.5f, 0.f },{ -0.5f, -0.5f, 0.f },{ 0.5f, -0.5f, 0.f } };
	command<primitive_orthographic>()->c = { {},{},{},{} };
	command<primitive_orthographic>()->i = { 0, 1, 2, 1, 3, 2 };
}

void dotth::rectangle::on_update(const float& delta)
{
}

void dotth::rectangle::set_color(const render::rgba & _color)
{
	for (auto& c : command<primitive_orthographic>()->c)
		c = _color;
}

void dotth::cube::init(void)
{
	assign_command<dotth::render::command::primitive_perspective>();
	command<primitive_perspective>()->_shader = dotth::shader_manager::instance()->find("mvp");
	command<primitive_perspective>()->_type = dotth::render::draw_type::perspective;
	command<primitive_perspective>()->v = { 
		{ -0.5f, +0.5f, -0.5f },{ +0.5f, +0.5f, -0.5f },{ -0.5f, -0.5f, -0.5f },{ +0.5f, -0.5f, -0.5f },	// front
		{ -0.5f, +0.5f, +0.5f },{ +0.5f, +0.5f, +0.5f },{ -0.5f, -0.5f, +0.5f },{ +0.5f, -0.5f, +0.5f },	// back
		//{ -0.5f, +0.5f, +0.5f },{ +0.5f, +0.5f, +0.5f },{ -0.5f, +0.5f, -0.5f },{ +0.5f, +0.5f, -0.5f },	// top
		//{ -0.5f, -0.5f, +0.5f },{ +0.5f, -0.5f, +0.5f },{ -0.5f, -0.5f, -0.5f },{ +0.5f, -0.5f, -0.5f },	// bottom
		//{ -0.5f, +0.5f, +0.5f },{ -0.5f, +0.5f, -0.5f },{ -0.5f, -0.5f, +0.5f },{ -0.5f, -0.5f, -0.5f },	// left
		//{ +0.5f, +0.5f, +0.5f },{ +0.5f, +0.5f, -0.5f },{ +0.5f, -0.5f, +0.5f },{ +0.5f, -0.5f, -0.5f },	// right
	};
	command<primitive_perspective>()->c = { 
		{1.f, 0.f, 0.f, 1.f},{ 0.f, 1.f, 0.f, 1.f },{ 0.f, 0.f, 1.f, 1.f },{},{},{},{},{ 1.f, 0.f, 0.f, 1.f } };
	command<primitive_perspective>()->i = { 
		0, 1, 2, 1, 3, 2,	// front
		4, 5, 6, 5, 7, 6,	// back
		4, 5, 0, 5, 1, 0,	// top
		6, 7, 2, 7, 2, 3,
		4, 0, 6, 0, 2, 6,
		1, 5, 3, 5, 7, 3,
	};
}

void dotth::cube::on_update(const float& delta)
{
	static float f = 0.f;
	trans()->rot_y(f);
	f += delta * 2.f;
}

void dotth::cube::set_color(const render::rgba & _color)
{
	for (auto& c : command<primitive_perspective>()->c)
		c = _color;
}