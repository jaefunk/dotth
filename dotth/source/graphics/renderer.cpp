#include "renderer.h"
#include "drawable.h"

bool dotth::renderer::initialize(HWND hwnd, int width, int height)
{
	return dotth::dx11::get()->initialize(hwnd, width, height);
}

void dotth::renderer::draw(void)
{
	dotth::dx11::get()->draw_begin();

	while (_queue.empty() == false)
	{
		if (auto p = _queue.front())
			p->draw();
		_queue.pop();
	}

	dotth::dx11::get()->draw_end();
}
