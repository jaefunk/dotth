#include "application.h"


bool dotth::application::init_application(void)
{
	return false;
}

bool dotth::application::init_renderer(void* handle, int width, int height)
{
	renderer::Instance()->Init(handle, width, height);
	return false;
}

bool dotth::application::loop(void)
{
	renderer::Instance()->clear_buffer();
	Scenario::Instance()->Loop();
	renderer::Instance()->swap_buffer();
	return true;
}
