
#pragma once
#include "graphics/dx11.h"
#include "utility/single_instance.h"

class renderer : public single_instance<renderer>
{
private:
	dx11 _dx11;
public:
	
	static ID3D11Device* device(void) {
		return renderer::get()->_dx11.device();
	}
	static ID3D11DeviceContext* context(void) {
		return renderer::get()->_dx11.context();
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