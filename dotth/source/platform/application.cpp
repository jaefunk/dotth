#include "application.h"


bool dotth::application::init_application(void)
{
	return false;
}

bool dotth::application::init_renderer(HWND hwnd, int width, int height)
{
	_renderer.initialize(hwnd, width, height);
	return false;
}

bool dotth::application::loop(void)
{
	_timer.update();
	_scenario.update();
	_renderer.draw();
	return true;
}
