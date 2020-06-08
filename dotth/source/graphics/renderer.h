
#pragma once
#include "graphics/dx11.h"
#include "utility/single_instance.h"

class drawable;
class renderer : public single_instance<renderer>
{
private:
	dx11 _dx11;
	std::queue<drawable*> _queue;

public:
	dx11* dx11(void) {
		return &_dx11;
	}
	void enqueue(drawable* pd);

public:
	bool initialize(HWND hwnd, int width, int height);
	void draw(void);
};