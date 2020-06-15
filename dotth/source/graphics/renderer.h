
#pragma once
#include "graphics/dx11.h"
#include "utility/single_instance.h"

class renderer : public single_instance<renderer>
{
private:
	dx11 _dx11;

public:
	dx11* dx11(void) {
		return &_dx11;
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