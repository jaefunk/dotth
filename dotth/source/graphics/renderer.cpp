#include "graphics/renderer.h"
#include "Graphics/RHI/D11/D11RHI.h"


bool renderer::Init(void* handle, int width, int height)
{
	return _dx11.Init(handle, width, height);
}
