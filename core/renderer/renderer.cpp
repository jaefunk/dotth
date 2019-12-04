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
#include "shader.hpp"
#include "base/resource.hpp"
#include "base/drawable.hpp"
#include "camera.hpp"

void dotth::gl_callback::display(void) {
	
	utility::timer::instance()->update();
	scene_manager::instance()->update();
	scene_manager::instance()->draw();
	camera::instance()->sync_all();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	renderer::instance()->process(dotth::render::draw_type::perspective);
	renderer::instance()->flush();
	glutSwapBuffers();
	glutPostRedisplay();
}

void dotth::gl_callback::reshape(int width, int height) {
    
	camera::instance()->set_pers(1.f, 100.f, static_cast<float>(width), static_cast<float>(height), 60.f);
	camera::instance()->set_view(vector3(0.f, 0.f, 5.f), vector3(0.f, 1.f, 0.f), vector3(0.f, 0.f, 0.f));
	camera::instance()->set_ortho_near(-1.f);
	camera::instance()->set_ortho_far(1.f);
	float ratio = width / height;
	camera::instance()->set_ltrb(-ratio, -1.f, ratio, 1.f);
	glViewport(0, 0, width, height);
	glutPostRedisplay();
}

void dotth::renderer::init_gl(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA|GLUT_DOUBLE|GLUT_DEPTH);
    glutInitWindowSize(1024, 512);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("asdf");
    glClearColor(0, 0, 0, 0);
	glEnable(GL_BLEND);
    glEnable(GL_POINT_SMOOTH);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_POLYGON_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glutDisplayFunc(dotth::gl_callback::display);
    glutReshapeFunc(dotth::gl_callback::reshape);

#ifdef WIN32
	if (glewInit() == GLEW_OK)
#endif
	{
        dotth::shader_manager::instance()->load("simple", "resources/glsl/Simple.glsl");
		dotth::shader_manager::instance()->load("mvp", "resources/glsl/mvp.glsl");
        dotth::resource_manager::instance()->load(type::resource::image, "resources/cat2.png", "cat");
        dotth::resource_manager::instance()->load(type::resource::image, "resources/usagi.png", "usagi");
	}

	glutMainLoop();
}

void dotth::renderer::flush(void)
{
	for (auto& q : queue)
		q.second.clear();
}

void dotth::renderer::push_back(drawable * drawable)
{
	queue[drawable->draw_type()].push_back(drawable);
}

void dotth::renderer::process(const dotth::render::draw_type & type) {
	queue[type].process();
}
