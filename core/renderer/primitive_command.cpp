#include "primitive_command.hpp"
#include "camera.hpp"

void dotth::render::command::primitive::draw(void) 
{
	_shader.bind();

	auto ot = glGetUniformLocation(_shader.program(), "ortho");
	glUniformMatrix4fv(ot, 1, GL_FALSE, camera::instance()->ortho());
	auto m = glGetUniformLocation(_shader.program(), "model");
	glUniformMatrix4fv(m, 1, GL_FALSE, _model);
	auto vtx = glGetAttribLocation(_shader.program(), "vertex");
	glEnableVertexAttribArray(vtx);
	glVertexAttribPointer(vtx, 3, GL_FLOAT, GL_FALSE, 0, v.data());
	auto clr = glGetAttribLocation(_shader.program(), "color");
	glEnableVertexAttribArray(clr);
	glVertexAttribPointer(clr, 4, GL_FLOAT, GL_FALSE, 0, c.data());
	glDrawElements(GL_TRIANGLES, static_cast<int32_t>(i.size()), GL_UNSIGNED_INT, i.data());

	_shader.unbind();
}
