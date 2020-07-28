#include "graphics/renderer.h"
#include "graphics/dx11.h"


bool renderer::initialize(HWND hwnd, int width, int height)
{
	_dx11.initialize(hwnd, width, height);
	return true;
}
