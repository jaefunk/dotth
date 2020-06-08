#include "application.h"


bool dotth::application::init_application(void)
{
	return false;
}

bool dotth::application::init_renderer(HWND hwnd, int width, int height)
{
	renderer::get()->initialize(hwnd, width, height);
	return false;
}

bool dotth::application::loop(void)
{
	_timer.update();
	scenario::get()->update();
	renderer::get()->draw();
	return true;
}
