#include "renderer.hpp"
#include "base/scene.hpp"
#include "resource/resource.hpp"
#include "resource/shader.hpp"
#include "camera.hpp"

void dotth::gl_callback::display(void) {
	
	utility::timer::instance()->update();
	scene_manager::instance()->update();
	camera::instance()->sync_all();
	scene_manager::instance()->draw();
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	renderer::instance()->process(dotth::render::draw_type::perspective);
	renderer::instance()->process(dotth::render::draw_type::orthographic);

	renderer::instance()->flush();

	glutSwapBuffers();
	glutPostRedisplay();
}

void dotth::gl_callback::reshape(int width, int height) {
    
	camera::instance()->set_pers(0.1f, 100.f, static_cast<float>(width), static_cast<float>(height), 90.f);
	camera::instance()->set_view(vector3(0.f, 2.f, -5.f), vector3(0.f, 1.f, 0.f), vector3(0.f, 0.f, 0.f));
	camera::instance()->set_ortho_near(-1.f);
	camera::instance()->set_ortho_far(1.f);
	float ratio = width / height / 2.f;
	camera::instance()->set_ltrb(-ratio, 0.5f, ratio, -0.5f);
	camera::instance()->set_ortho1px(1.f / static_cast<float>(height));
	glViewport(0, 0, width, height);
	glutPostRedisplay();
}

void dotth::renderer::init_gl(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA|GLUT_DOUBLE|GLUT_DEPTH);
    glutInitWindowSize(1024, 512);
    glutInitWindowPosition(0, 0);
    glClearColor(0, 0, 0, 0);
	glutCreateWindow("asdf");
	glEnable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
	
    glutDisplayFunc(dotth::gl_callback::display);
    glutReshapeFunc(dotth::gl_callback::reshape);

#ifdef WIN32
	if (glewInit() == GLEW_OK)
#endif
	{
        dotth::resource_manager::instance()->load(type::resource::shader, "resources/glsl/Simple.glsl", "simple");
		dotth::resource_manager::instance()->load(type::resource::shader, "resources/glsl/mvp.glsl", "mvp");
		dotth::resource_manager::instance()->load(type::resource::shader, "resources/glsl/ortho.glsl", "ortho");
        dotth::resource_manager::instance()->load(type::resource::image, "resources/cat2.png", "cat");
        dotth::resource_manager::instance()->load(type::resource::image, "resources/usagi.png", "usagi");
	}

	glutMainLoop();
}

void dotth::renderer::flush(void)
{
	for (auto& q : _queue)
		q.second.clear();
}

void dotth::renderer::push_back(dotth::render::command::inherit * inherit)
{
	_queue[inherit->_type].push_back(inherit);
}

void dotth::renderer::process(const dotth::render::draw_type & type) {
	_queue[type].process();
}
