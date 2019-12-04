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


//dotth::rectangle::rectangle(void) : dotth::drawable(dotth::render::draw_type::perspective)
//{
//	set_shader("simple");
//}
//
//void dotth::rectangle::init(void)
//{
//	_vertex_list.v = { xyz(-0.5f, 0.5f, 0.f), xyz(0.5f, 0.5f, 0.f), xyz(-0.5f, -0.5f, 0.f), xyz(0.5f, -0.5f, 0.f) };
//	_vertex_list.c = { rgba(), rgba(), rgba(), rgba() };
//	_vertex_list.u = { uv(0.f, 1.f), uv(1.f, 1.f), uv(0.f, 0.f), uv(1.f, 0.f) };
//    _vertex_list.i = { 0, 1, 2, 1, 3, 2 };
//}
//
//void dotth::rectangle::load_sprite(const char * name) 
//{
//	_texture = dotth::resource_manager::instance()->find<texture>(name);
//	if (_texture == nullptr)
//		printf("%s is not valid sprite", name);
//}
//
//void dotth::rectangle::draw(const int flags)
//{
//	if (_texture)
//		_texture->bind();
//	if (_shader)
//		_shader->bind();
//
//	auto p = glGetAttribLocation(_shader->program(), "position");
//	glEnableVertexAttribArray(p);
//	glVertexAttribPointer(p, 3, GL_FLOAT, GL_FALSE, 0, _vertex_list.v.data());
//
//	auto c = glGetAttribLocation(_shader->program(), "color");
//	glEnableVertexAttribArray(c);
//	glVertexAttribPointer(c, 4, GL_FLOAT, GL_FALSE, 0, _vertex_list.c.data());
//
//	auto uv = glGetAttribLocation(_shader->program(), "uv");
//	glEnableVertexAttribArray(uv);
//	glVertexAttribPointer(uv, 2, GL_FLOAT, GL_FALSE, 0, _vertex_list.u.data());
//
//	glDrawElements(GL_TRIANGLES, static_cast<int32_t>(_vertex_list.i.size()), GL_UNSIGNED_INT, _vertex_list.i.data());
//
//	if (_texture)
//		_texture->unbind();
//	if (_shader)
//		_shader->unbind();
//}

//void dotth::cube::init(void)
//{
//    _command._triangle.v.clear();
//    _command._triangle.v.push_back(xyz(0.5f, 0.5f, -0.5f));
//    _command._triangle.v.push_back(xyz(0.5f, 0.5f, 0.5f));
//    _command._triangle.v.push_back(xyz(0.5f, -0.5f, -0.5f));
//    _command._triangle.v.push_back(xyz(0.5f, -0.5f, 0.5f));
//    _command._triangle.v.push_back(xyz(-0.5f, 0.5f, -0.5f));
//    _command._triangle.v.push_back(xyz(0.5f, 0.5f, -0.5f));
//    _command._triangle.v.push_back(xyz(-0.5f, -0.5f, -0.5f));
//    _command._triangle.v.push_back(xyz(0.5f, -0.5f, -0.5f));
//    _command._triangle.v.push_back(xyz(-0.5f, 0.5f, 0.5f));
//    _command._triangle.v.push_back(xyz(0.5f, 0.5f, 0.5f));
//    _command._triangle.v.push_back(xyz(-0.5f, 0.5f, -0.5f));
//    _command._triangle.v.push_back(xyz(0.5f, 0.5f, -0.5f));
//    _command._triangle.v.push_back(xyz(-0.5f, -0.5f, -0.5f));
//    _command._triangle.v.push_back(xyz(0.5f, -0.5f, -0.5f));
//    _command._triangle.v.push_back(xyz(-0.5f, -0.5f, 0.5f));
//    _command._triangle.v.push_back(xyz(0.5f, -0.5f, 0.5f));
//    _command._triangle.v.push_back(xyz(-0.5f, 0.5f, -0.5f));
//    _command._triangle.v.push_back(xyz(-0.5f, 0.5f, 0.5f));
//    _command._triangle.v.push_back(xyz(-0.5f, -0.5f, -0.5f));
//    _command._triangle.v.push_back(xyz(-0.5f, -0.5f, 0.5f));
//    _command._triangle.v.push_back(xyz(-0.5f, 0.5f, 0.5f));
//    _command._triangle.v.push_back(xyz(0.5f, 0.5f, 0.5f));
//    _command._triangle.v.push_back(xyz(-0.5f, -0.5f, 0.5f));
//    _command._triangle.v.push_back(xyz(0.5f, -0.5f, 0.5f));
//
//    _command._triangle.u.clear();
//    for (auto i = 0; i < 6; ++i)
//    {
//        _command._triangle.u.push_back(uv(0.f, 0.f));
//        _command._triangle.u.push_back(uv(1.f, 0.f));
//        _command._triangle.u.push_back(uv(0.f, 1.f));
//        _command._triangle.u.push_back(uv(1.f, 1.f));
//    }
//
//    _command._triangle.i.clear();
//    for (auto i = 0; i < 6; ++i)
//    {
//        _command._triangle.i.push_back(0 + 4 * i);
//        _command._triangle.i.push_back(1 + 4 * i);
//        _command._triangle.i.push_back(2 + 4 * i);
//        _command._triangle.i.push_back(1 + 4 * i);
//        _command._triangle.i.push_back(3 + 4 * i);
//        _command._triangle.i.push_back(2 + 4 * i);
//    }
//
//    _command._triangle.c.clear();
//    for (std::size_t i = 0; i < _command._triangle.v.size(); ++i)
//        _command._triangle.c.push_back(rgba());
//}
//
//void dotth::cube::draw(int flags) {
//    if (_command._triangle.v.empty())
//        return;
//    renderer::instance()->push(&_command);
//}
