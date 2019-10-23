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

#include <algorithm>

#define GL_SILENCE_DEPRECATION
#ifndef WIN32
#include <GLUT/GLUT.h>
#else
#include "external\opengl\win\glut.h"
#endif

#include "renderer.hpp"
#include "base\scene.hpp"

void dotth::gl_callback::display(void) {
	utility::timer::instance()->update();
	scene_manager::instance()->update();
	scene_manager::instance()->draw();

	glClear(GL_COLOR_BUFFER_BIT);
	auto queue = renderer::instance()->find_render_queue(render_queue_type::perspective);
	queue.process();

	//// flush the drawing to screen .
	glutSwapBuffers();
	glutPostRedisplay();
}

void dotth::gl_callback::reshape(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(30, static_cast<double>(width)/static_cast<double>(height), 1.0, 50.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 5.0, 0, 0.0, 0.0, 0.0, 1.0, 0.0);
    glutPostRedisplay();
}

void dotth::renderer::init_gl(int argc, char** argv) {
	
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
    glutInitWindowSize(1024, 512);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("asdf");
    glClearColor(0, 0, 0, 0);
    glEnable(GL_POINT_SMOOTH);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_POLYGON_SMOOTH);
    
    
    glutReshapeFunc(dotth::gl_callback::reshape);
    glutDisplayFunc(dotth::gl_callback::display);
//    glutTimerFunc(15, dotth::gl_callback::timer, 0);
    glutMainLoop();
}

//1void dotth::render_queue::process_command(const decltype(commands)::value_type p)
//{
//	switch (p->type())
//	{
//	case render_command_type::unknown: break;
//	case render_command_type::triangles:
//		auto jj = static_cast<triangle_command*>(p);
//		for (auto const& vertex : jj->_triangle.vertexs)
//		{
//			glColor4f(vertex.r, vertex.g, vertex.b, vertex.a);
//			glVertex3f(vertex.x, vertex.y, vertex.z);
//		}
//		break;
//	default: break;
//	}
//}

void dotth::render_queue::process(void)
{
	std::for_each(std::begin(commands), std::end(commands), [](render_command* p) {
		switch (p->type())
		{
		case render_command_type::unknown: break;
		case render_command_type::polygons:
		{
			auto jj = static_cast<polygon_command*>(p);
			glEnableClientState(GL_VERTEX_ARRAY);
			glVertexPointer(3, GL_FLOAT, 0, jj->_triangle.v.data());
			glEnableClientState(GL_COLOR_ARRAY);
			glColorPointer(4, GL_FLOAT, 0, jj->_triangle.c.data());
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, jj->_triangle.i.data());
		}	
			break;
		default: break;
		}
	});
}
