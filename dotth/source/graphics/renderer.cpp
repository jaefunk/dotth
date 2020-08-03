#include "Graphics/Renderer.h"
#include "Graphics/RHI/D11/D11RHI.h"


bool Renderer::Init(void* handle, int width, int height)
{
	_RHI = new D11RHI;
	return _RHI->Init(handle, width, height);
}
