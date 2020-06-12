#include "graphics/renderer.h"
#include "graphics/dx11.h"
#include "graphics/drawable.h"


bool renderer::initialize(HWND hwnd, int width, int height)
{
	_dx11.initialize(hwnd, width, height);
	return true;
}
