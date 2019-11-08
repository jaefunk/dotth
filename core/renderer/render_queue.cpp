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

#define GL_SILENCE_DEPRECATION
#ifndef WIN32
#include <GLUT/GLUT.h>
#else
#include "../external/opengl/glew.h"
#include "../external/opengl/glut.h"
#endif

#include "render_queue.hpp"

void dotth::render_queue::push_back(dotth::render_command * command) {
	commands.push_back(command);
}

void dotth::render_queue::clear(void) {
	commands.clear();
}

void dotth::render_queue::process(void)
{
	std::for_each(std::begin(commands), std::end(commands), [](dotth::render_command* p) {
		switch (p->type())
		{
		case render_command_type::unknown: break;
		case render_command_type::polygons:
		{
			auto jj = static_cast<polygon_command*>(p);

			int use_program = 3;
			glUseProgram(use_program);

			glEnableClientState(GL_VERTEX_ARRAY);
			glEnableClientState(GL_COLOR_ARRAY);

			glVertexPointer(3, GL_FLOAT, 0, jj->_triangle.v.data());
			glColorPointer(4, GL_FLOAT, 0, jj->_triangle.c.data());

			auto uv = glGetAttribLocation(use_program, "in_uv");
			glEnableVertexAttribArray(uv);
			glVertexAttribPointer(uv, 2, GL_FLOAT, GL_FALSE, 0, jj->_triangle.u.data());

			glDrawElements(GL_TRIANGLES, static_cast<int32_t>(jj->_triangle.i.size()), GL_UNSIGNED_INT, jj->_triangle.i.data());
			glUseProgram(0);
		}
		break;
		default: break;
		}
	});
	clear();
}
