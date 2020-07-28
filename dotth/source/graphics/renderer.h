
#pragma once
#include "Graphics/D3D11RHI.h"
#include "utility/SingleInstance.h"

class renderer : public SingleInstance<renderer>
{
private:
	D3D11RHI _dx11;
public:
	
	static ID3D11Device* device(void) {
		return renderer::Instance()->_dx11.device();
	}
	static ID3D11DeviceContext* context(void) {
		return renderer::Instance()->_dx11.context();
	}

public:
	bool initialize(HWND hwnd, int width, int height);
	void clear_buffer(void)
	{
		_dx11.draw_begin();
	}
	void swap_buffer(void)
	{
		_dx11.draw_end();
	}
};