#include "renderer.hpp"
#include "base/scene.hpp"
#include "resource/resource.hpp"
#include "camera.hpp"

void dotth::gl_callback::display(void) {
	
	utility::timer::instance()->update();
	scene_manager::instance()->update();
	camera::instance()->sync_all();
	scene_manager::instance()->draw();
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	renderer::instance()->process(dotth::render::draw_type::perspective);
	renderer::instance()->process(dotth::render::draw_type::orthographic);


	//unsigned int fbo;
	//glGenFramebuffers(1, &fbo);
	//glBindFramebuffer(GL_FRAMEBUFFER, fbo);
	//glClearColor(0.1f, 0.1f, 0.1f, 1.f);
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glEnable(GL_DEPTH_TEST);
	//glDepthFunc(GL_LESS);
	//renderer::instance()->process(dotth::render::draw_type::perspective);
	//glBindFramebuffer(GL_FRAMEBUFFER, 0);


	renderer::instance()->flush();

	glutSwapBuffers();
	glutPostRedisplay();
}

void dotth::gl_callback::reshape(int width, int height) {
    
	camera::instance()->set_pers(0.1f, 100.f, static_cast<float>(width), static_cast<float>(height), 60.f);
	camera::instance()->set_view(vector3(0.f, 5.f, -5.f), vector3(0.f, 1.f, 0.f), vector3(0.f, 0.f, 0.f));
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
	glutCreateWindow("asdf");
	glClearColor(0.25f, 0.25f, 0.25f, 1.f);
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
	printf("drawing_object_count: %d\n", _drawing_object_cnt);
	_drawing_object_cnt = 0;
}

void dotth::renderer::push_back(dotth::render::command::inherit * inherit)
{
	_drawing_object_cnt++;
	_queue[inherit->_type].push_back(inherit);

	//unsigned int fbo;
	//glGenFramebuffers(1, &fbo);
	//glBindFramebuffer(GL_FRAMEBUFFER, fbo);
	//glClearColor(0.1f, 0.1f, 0.1f, 1.f);
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glEnable(GL_DEPTH_TEST);
	//glBindFramebuffer(GL_FRAMEBUFFER, 0);
	//if (glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE)
	//{
	//	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, 999, 0);
	//}
	//glBindFramebuffer(GL_FRAMEBUFFER, 0);
	//glDeleteFramebuffers(1, &fbo);

	//unsigned int rbo;
	//glGenRenderbuffers(1, &rbo);
	//glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	//glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 1024, 512);
	//glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);
}

void dotth::renderer::process(const dotth::render::draw_type & type) {
	_queue[type].process();
}
