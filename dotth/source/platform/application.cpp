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
	renderer::get()->clear_buffer();
	Scenario::get()->Loop();
	renderer::get()->swap_buffer();
	return true;
}
