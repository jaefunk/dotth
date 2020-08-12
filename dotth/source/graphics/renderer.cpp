#include "Graphics/Renderer.h"

D11RHI * Renderer::RHI(void) 
{
	return Renderer::Instance()->_RHI;
}

bool Renderer::Init(void * handle, int width, int height)
{
	_RHI = new D11RHI;
	return _RHI->Init(handle, width, height);
}

void Renderer::clear_buffer(void)
{
	_RHI->PreDraw();
}

void Renderer::swap_buffer(void)
{
	_RHI->PostDraw();
}
