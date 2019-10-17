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

#include "renderer.hpp"

#define GL_SILENCE_DEPRECATION

#ifndef WIN32
#include <gl\GLU.h>
#else
#include "external\opengl\win\glut.h"
#endif

float dotth::gl_callback::_x = 0.f;
float dotth::gl_callback::_y = 0.f;
void dotth::gl_callback::display(void) {
	// clear the draw buffer .
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POLYGON); 
	{
		glColor3f(0.5, 0.0f, 0.0);
		glVertex3f(_x + 0.0, _y + 0.5, 0.0);
		glColor3f(0.0, 0.5, 0.0);
		glVertex3f(_x + -0.5, _y + 0.0, 0.0);
		glColor3f(0.0, 0.0, 0.5);
		glVertex3f(_x + 0.5, _y + 0.0, 0.0);
	} 
	glEnd();

	// flush the drawing to screen . 
	glFlush();
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

void dotth::gl_callback::keyboard(unsigned char key, int x, int y) {
	printf("%d, %d, %d\n", key, x, y);
	if (key == 100)
		_x += 0.01f;
	if (key == 97)
		_x -= 0.01f;

	if (key == 119)
		_y += 0.01f;
	if (key == 115)
		_y -= 0.01f;
}

void dotth::gl_callback::mouse(int button, int state, int x, int y) {
	printf("%d, %d, %d, %d\n", button, state, x, y);
}

void dotth::gl_callback::timer(int value) {
	glutPostRedisplay();
	glutTimerFunc(15, dotth::gl_callback::timer, 0);
}

void dotth::renderer::init_gl(int argc, char** argv) {
	
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA);
    glutInitWindowSize(1024, 512);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("asdf");
    glClearColor(0, 0, 0, 0);
    glutReshapeFunc(dotth::gl_callback::reshape);
    glutDisplayFunc(dotth::gl_callback::display);
	glutSetKeyRepeat(GLUT_KEY_REPEAT_OFF);
	glutTimerFunc(15, dotth::gl_callback::timer, 0);
	glutKeyboardFunc(dotth::gl_callback::keyboard);
	glutKeyboardUpFunc(dotth::gl_callback::keyboard);
	
	//glutMouseFunc(dotth::gl_callback::mouse);
    glutMainLoop();
}
