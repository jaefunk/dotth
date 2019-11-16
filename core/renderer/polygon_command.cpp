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

#include "polygon_command.hpp"
#include "renderer.hpp"
#include "texture.hpp"

void dotth::polygon_command::init(const dotth::drawinfo::polygon & triangle)
{
	_triangle = triangle;
}

const bool dotth::polygon_command::draw(void)
{
    if (_binded_texture != 0)
        glBindTexture(GL_TEXTURE_2D, _binded_texture);
        
	int use_program = 3;
	glUseProgram(use_program);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);

	glVertexPointer(3, GL_FLOAT, 0, _triangle.v.data());
	glColorPointer(4, GL_FLOAT, 0, _triangle.c.data());

	auto uv = glGetAttribLocation(use_program, "in_uv");
	glEnableVertexAttribArray(uv);
	glVertexAttribPointer(uv, 2, GL_FLOAT, GL_FALSE, 0, _triangle.u.data());

	glDrawElements(GL_TRIANGLES, static_cast<int32_t>(_triangle.i.size()), GL_UNSIGNED_INT, _triangle.i.data());
	glUseProgram(0);
    
    if (_binded_texture != 0)
        glBindTexture(GL_TEXTURE_2D, 0);
	return true;
}
