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
#include "base/scene.hpp"
#include "platform/filesystem/path.hpp"
#include "shader.hpp"
#include "base/resource.hpp"

void dotth::gl_callback::display(void) {

	utility::timer::instance()->update();
	scene_manager::instance()->update();
	scene_manager::instance()->draw();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if (auto queue = renderer::instance()->find_render_queue(render_queue_type::perspective))
	{
		queue->process();
		queue->clear();
	}
	glutSwapBuffers();
	glutPostRedisplay();
}

void dotth::gl_callback::reshape(int width, int height) {
    
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, static_cast<double>(width) / static_cast<double>(height), 1.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glutPostRedisplay();
    gluLookAt(0.0, 0.0, 5.0, 0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void dotth::renderer::init_gl(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA|GLUT_DOUBLE|GLUT_DEPTH);
    glutInitWindowSize(1024, 512);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("asdf");
    glClearColor(0, 0, 0, 0);

    glEnable(GL_POINT_SMOOTH);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_POLYGON_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glutDisplayFunc(dotth::gl_callback::display);
    glutReshapeFunc(dotth::gl_callback::reshape);
    queue[render_queue_type::perspective] = std::make_shared<render_queue>();
//#ifdef WIN32
	if (glewInit() == GLEW_OK)
//#endif
	{
        dotth::shader_manager::instance()->load("simple", dotth::path("resources/glsl/Simple.glsl").c_str());
        dotth::resource_manager::instance()->load(type::resource::image, "resources/cat2.png", "cat");
        dotth::resource_manager::instance()->load(type::resource::image, "resources/usagi.png", "usagi");
        glutMainLoop();
	}
}

void dotth::renderer::push(dotth::render_command * command)
{
	switch (command->type()) {
	case render_command_type::polygons:
            queue[render_queue_type::perspective]->push_back(command);
            break;
	case render_command_type::unknown:
            break;
	default:
            break;
	}
}

const std::shared_ptr<dotth::render_queue> dotth::renderer::find_render_queue(const render_queue_type & type) {
	return queue[type];
}
