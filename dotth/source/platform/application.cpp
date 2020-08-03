#include "application.h"


bool dotth::application::init_application(void)
{
	return false;
}

bool dotth::application::init_renderer(void* handle, int width, int height)
{
	Renderer::Instance()->Init(handle, width, height);
	return false;
}

bool dotth::application::loop(void)
{
	Renderer::Instance()->clear_buffer();
	Scenario::Instance()->Loop();
	Renderer::Instance()->swap_buffer();
	return true;
}
