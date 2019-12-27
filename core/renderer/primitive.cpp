#include "primitive.hpp"
#include "primitive_command.hpp"

void dotth::rectangle::init(void)
{
	assign_command<primitive_orthographic>();
	command<primitive_orthographic>()->_type = dotth::render::draw_type::orthographic;
	command<primitive_orthographic>()->_shader = *dotth::resource_manager::instance()->find<shader>("ortho");
	command<primitive_orthographic>()->v = { { -0.5f, 0.5f, 0.f },{ 0.5f, 0.5f, 0.f },{ -0.5f, -0.5f, 0.f },{ 0.5f, -0.5f, 0.f } };
	command<primitive_orthographic>()->c = { {},{},{},{} };
	command<primitive_orthographic>()->i = { 0, 1, 2, 1, 3, 2 };
}

void dotth::rectangle::on_update(const float& delta)
{
	//static float f = 0.f;
	////f += delta * 1.f;
	////trans()->rot_x(f);
	////f += delta * 2.f;
	////trans()->rot_y(f);
	//f += delta * 5.f;

	//trans().rot_z(f);
}

void dotth::rectangle::set_color(const render::rgba & _color)
{
	for (auto& c : command<primitive_orthographic>()->c)
		c = _color;
}

void dotth::cube::init(void)
{
	assign_command<primitive_perspective>();
	command<primitive_perspective>()->_type = dotth::render::draw_type::perspective;
	command<primitive_perspective>()->_shader = *dotth::resource_manager::instance()->find<shader>("mvp");
	command<primitive_perspective>()->v = {
		{ -0.5f, +0.5f, -0.5f },{ +0.5f, +0.5f, -0.5f },{ -0.5f, -0.5f, -0.5f },{ +0.5f, -0.5f, -0.5f },	// front
		{ -0.5f, +0.5f, +0.5f },{ +0.5f, +0.5f, +0.5f },{ -0.5f, -0.5f, +0.5f },{ +0.5f, -0.5f, +0.5f },	// back
	};
	command<primitive_perspective>()->c = {
		{ 1.f, 0.f, 0.f, 0.5f },{ 0.f, 1.f, 0.f, 0.5f },{ 0.f, 0.f, 1.f, 0.5f },{ 0.f, 1.f, 1.f, 0.5f },
		{ 0.f, 1.f, 1.f, 0.5f },{ 0.f, 0.f, 1.f, 0.5f },{ 0.f, 1.f, 0.f, 0.5f },{ 1.f, 0.f, 0.f, 0.5f }
	};
	command<primitive_perspective>()->i = {
		0, 1, 2, 1, 3, 2,	// front
		4, 5, 6, 5, 7, 6,	// back
		4, 5, 0, 5, 1, 0,	// top
		6, 7, 2, 7, 2, 3,	// bottom
		4, 0, 6, 0, 2, 6,	// left
		1, 5, 3, 5, 7, 3,	// right
	};
}

void dotth::cube::on_update(const float& delta)
{
	static float f = 0.f;
	//f += delta * 1.f;
	//trans()->rot_x(f);
	//f += delta * 2.f;
	//trans()->rot_y(f);
	
	f += delta;
	trans().rot_z(f/2);
	trans().rot_x(f/3);
	trans().rot_y(f/4);
}