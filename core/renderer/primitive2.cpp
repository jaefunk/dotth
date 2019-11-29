/*
Licensed under the MIT License <http://opensource.org/licenses/MIT>.
Copyright (c) 2019 jaefunk <https://github.com/jaefunk/dotth>.

Permission is hereby  granted, free of charge, to any  person obtaining a copy
of this software and associated  documentation files (the "Software"), to deal
in the Software  without restriction, including without  limitation the rights
to  use, copy,  modify, merge,  publish, distribute,  sublicense, and/or  sell
copies  of  the Software,  and  to  permit persons  to  whom  the Software  is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE  IS PROVIDED "AS  IS", WITHOUT WARRANTY  OF ANY KIND,  EXPRESS OR
IMPLIED,  INCLUDING BUT  NOT  LIMITED TO  THE  WARRANTIES OF  MERCHANTABILITY,
FITNESS FOR  A PARTICULAR PURPOSE AND  NONINFRINGEMENT. IN NO EVENT  SHALL THE
AUTHORS  OR COPYRIGHT  HOLDERS  BE  LIABLE FOR  ANY  CLAIM,  DAMAGES OR  OTHER
LIABILITY, WHETHER IN AN ACTION OF  CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE  OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "primitive2.hpp"
#include "renderer.hpp"
#include "texture.hpp"

dotth::rectangle2::rectangle2(void) : dotth::drawable(dotth::render::draw_type::perspective)
{
	set_shader("mvp");
}

void dotth::rectangle2::init(void)
{
	_vertex_list.v = { xyz(-0.5f, 0.5f, 0.f), xyz(0.5f, 0.5f, 0.f), xyz(-0.5f, -0.5f, 0.f), xyz(0.5f, -0.5f, 0.f) };
	_vertex_list.c = { rgba(), rgba(), rgba(), rgba() };
	_vertex_list.u = { uv(0.f, 1.f), uv(1.f, 1.f), uv(0.f, 0.f), uv(1.f, 0.f) };
    _vertex_list.i = { 0, 1, 2, 1, 3, 2 };
}

void dotth::rectangle2::load_sprite(const char * name)
{
	_texture = dotth::resource_manager::instance()->find<texture>(name);
	if (_texture == nullptr)
		printf("%s is not valid sprite", name);
}

void dotth::rectangle2::draw(const int flags)
{
	if (_texture)
		_texture->bind();
	if (_shader)
		_shader->bind();

	auto m = glGetUniformLocation(_shader->program(), "model");
	//glUniformMatrix4fv(m, 16, GL_FALSE, trans.matrix().m);
	glUniformMatrix4fv(m, 16, GL_FALSE, matrix4::identity.m);

	auto v = glGetUniformLocation(_shader->program(), "view");
	glUniformMatrix4fv(v, 16, GL_FALSE, renderer::instance()->get_camera()->view());

	auto p = glGetUniformLocation(_shader->program(), "proj");
	glUniformMatrix4fv(p, 16, GL_FALSE, renderer::instance()->get_camera()->proj());


	auto pos = glGetAttribLocation(_shader->program(), "position");
	glEnableVertexAttribArray(pos);
	glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, 0, _vertex_list.v.data());

	auto col = glGetAttribLocation(_shader->program(), "color");
	glEnableVertexAttribArray(col);
	glVertexAttribPointer(col, 4, GL_FLOAT, GL_FALSE, 0, _vertex_list.c.data());

	auto uv = glGetAttribLocation(_shader->program(), "uv");
	glEnableVertexAttribArray(uv);
	glVertexAttribPointer(uv, 2, GL_FLOAT, GL_FALSE, 0, _vertex_list.u.data());

	glDrawElements(GL_TRIANGLES, static_cast<int32_t>(_vertex_list.i.size()), GL_UNSIGNED_INT, _vertex_list.i.data());

	if (_texture)
		_texture->unbind();
	if (_shader)
		_shader->unbind();
}
