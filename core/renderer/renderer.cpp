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

#include "renderer.hpp"
#include "../base/scene.hpp"
#include "../external/stb/image/stb_image.h"
#include "shader.hpp"


void dotth::gl_callback::display(void) {

	utility::timer::instance()->update();
	scene_manager::instance()->update();
	scene_manager::instance()->draw();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	auto queue = renderer::instance()->find_render_queue(render_queue_type::perspective);
	queue.process();

	// flush the drawing to screen .
	glutSwapBuffers();
	glutPostRedisplay();
}

void dotth::gl_callback::reshape(int width, int height) {
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(30, static_cast<double>(width) / static_cast<double>(height), 1.0, 50.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(2.0, 3.0, -5.0, 0, 0.0, 0.0, 0.0, 1.0, 0.0);
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
	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);
	glutReshapeFunc(dotth::gl_callback::reshape);
	glutDisplayFunc(dotth::gl_callback::display);

#ifdef WIN32
	if (glewInit() == GLEW_OK)
#endif
	{
#ifdef WIN32
        auto program_id = dotth::shader::LoadShaders("../../resources/glsl/Simple.vs", "../../resources/glsl/Simple.fs");
#else
        auto program_id = dotth::shader::LoadShaders("resources/glsl/Simple.vs", "resources/glsl/Simple.fs");
#endif
		
        unsigned int texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        int X, Y, c1;
        //stbi_set_flip_vertically_on_load(true);
        auto b = stbi_load("../../resources/usagi.png", &X, &Y, &c1, 0);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, X, Y, 0, GL_RGBA, GL_UNSIGNED_BYTE, b);
        glGenerateMipmap(GL_TEXTURE_2D);
        stbi_image_free(b);

		glutMainLoop();
	}
	
}

void dotth::render_queue::process(void)
{
	std::for_each(std::begin(commands), std::end(commands), [](render_command* p) {
		switch (p->type())
		{
		case render_command_type::unknown: break;
		case render_command_type::polygons:
		{
			auto jj = static_cast<polygon_command*>(p);

            int use_program = 3;
			glUseProgram(use_program);
            
			glEnableClientState(GL_VERTEX_ARRAY);
			//glEnableClientState(GL_COLOR_ARRAY);
            
            glVertexPointer(3, GL_FLOAT, 0, jj->_triangle.v.data());
            //glColorPointer(4, GL_FLOAT, 0, jj->_triangle.c.data());
            
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
}
