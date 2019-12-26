#include "gl_global_callback.hpp"
#include "camera.hpp"
#include "renderer.hpp"
#include "base/scene.hpp"
#include "base/input.hpp"

void dotth::gl_global_callback::display(void) 
{
    printf("%f\n", dotth::utility::timer::instance()->delta());
    utility::timer::instance()->update();
    scene_manager::instance()->update();
    camera::instance()->sync_all();
    scene_manager::instance()->draw();
    
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	renderer::instance()->process(dotth::render::draw_type::perspective);
	renderer::instance()->process(dotth::render::draw_type::orthographic);
    
	renderer::instance()->flush();
	input::instance()->flush();
    glutSwapBuffers();
    glutPostRedisplay();
}

void dotth::gl_global_callback::reshape(int width, int height) 
{
	camera::instance()->set_pers(0.1f, 100.f, static_cast<float>(width), static_cast<float>(height), 60.f);
	camera::instance()->set_view(vector3(0.f, 5.f, -5.f), vector3(0.f, 1.f, 0.f), vector3(0.f, 0.f, 0.f));
	camera::instance()->set_ortho_near(-1.f);
	camera::instance()->set_ortho_far(1.f);
	float ratio = width / height / 2.f;
	camera::instance()->set_ltrb(-ratio, 0.5f, ratio, -0.5f);
	camera::instance()->set_ortho1px(1.f / static_cast<float>(height));
//	glViewport(0, 0, width, height);
//	glutSwapBuffers();
//	glutPostRedisplay();
}

void dotth::gl_global_callback::timer(int value)
{
	
    
	glutTimerFunc(1, dotth::gl_global_callback::timer, 0);
}

void dotth::gl_global_callback::keyboard(unsigned char key, int x, int y)
{
	input::instance()->push_keyboard_input(key);
}

void dotth::gl_global_callback::mouse(int button, int state, int x, int y)
{
	input::instance()->push_mouse_input(x, y, button, state);
}

void dotth::gl_global_callback::motion(int x, int y)
{
	input::instance()->push_mouse_move(x, y);
}
