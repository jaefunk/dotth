#include "primitive.hpp"
#include "camera.hpp"

dotth::rectangle::rectangle(void) : dotth::drawable(dotth::render::draw_type::perspective)
{
	set_shader("mvp");
}

void dotth::rectangle::init(void)
{
	_vertex.v = { {-0.5f, 0.5f, 0.f}, {0.5f, 0.5f, 0.f}, {-0.5f, -0.5f, 0.f}, {0.5f, -0.5f, 0.f} };
	_vertex.c = { {}, {}, {}, {} };
	_vertex.i = { 0, 1, 2, 1, 3, 2 };
}

void dotth::rectangle::set_color(const render::rgba & _color)
{
	for (auto& c : _vertex.c)
		c = _color;
}

void dotth::rectangle::on_update(const float& delta)
{

}

void dotth::rectangle::draw(const int flags)
{
	if (_shader)
		_shader->bind();

	auto vp = glGetUniformLocation(_shader->program(), "view_pers");
	glUniformMatrix4fv(vp, 1, GL_FALSE, camera::instance()->view_pers());
	//glUniformMatrix4fv(vp, 1, GL_FALSE, camera::instance()->ortho());
	auto m = glGetUniformLocation(_shader->program(), "model");
	glUniformMatrix4fv(m, 1, GL_FALSE, trans.result());
	auto vtx = glGetAttribLocation(_shader->program(), "vertex");
	glEnableVertexAttribArray(vtx);
	glVertexAttribPointer(vtx, 3, GL_FLOAT, GL_FALSE, 0, _vertex.v.data());
	auto col = glGetAttribLocation(_shader->program(), "color");
	glEnableVertexAttribArray(col);
	glVertexAttribPointer(col, 4, GL_FLOAT, GL_FALSE, 0, _vertex.c.data());
	glDrawElements(GL_TRIANGLES, static_cast<int32_t>(_vertex.i.size()), GL_UNSIGNED_INT, _vertex.i.data());

	if (_shader)
		_shader->unbind();
}
