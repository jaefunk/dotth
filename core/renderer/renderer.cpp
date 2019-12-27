#include "renderer.hpp"
#include "gl_global_callback.hpp"
#include "base/scene.hpp"
#include "resource/resource.hpp"
#include "camera.hpp"

void dotth::renderer::init_gl(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA|GLUT_DOUBLE|GLUT_DEPTH);
    glutInitWindowSize(1024, 512);
    glutInitWindowPosition(0, 0);
	glutCreateWindow("asdf");
	glClearColor(0.5f, 0.5f, 0.5f, 1.f);
	glEnable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
	
    glutDisplayFunc(dotth::gl_global_callback::display);
    glutReshapeFunc(dotth::gl_global_callback::reshape);

	glutTimerFunc(1, dotth::gl_global_callback::timer, 0);
	glutKeyboardFunc(dotth::gl_global_callback::keyboard);
	glutMouseFunc(dotth::gl_global_callback::mouse);
	glutMotionFunc(dotth::gl_global_callback::motion);

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
	//printf("drawing_object_count: %d\n", _drawing_object_cnt);
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
