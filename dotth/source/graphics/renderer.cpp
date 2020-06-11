#include "graphics/renderer.h"
#include "graphics/dx11.h"
#include "graphics/drawable.h"


void renderer::enqueue(drawable * pd)
{
	_queue.push(pd);
}

bool renderer::initialize(HWND hwnd, int width, int height)
{
	_dx11.initialize(hwnd, width, height);
	return true;
}

void renderer::draw(void)
{
	_dx11.draw_begin();

	while (_queue.empty() == false)
	{
		if (auto p = _queue.front())
			p->draw(_dx11.context());
		_queue.pop();
	}

	_dx11.draw_end();
}
