#include "graphics/renderer.h"
#include "Graphics/D3D11RHI.h"


bool renderer::initialize(HWND hwnd, int width, int height)
{
	_dx11.initialize(hwnd, width, height);
	return true;
}
