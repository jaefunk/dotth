#include "renderer.h"
#include "drawable.h"

bool dotth::renderer::initialize(HWND hwnd, int width, int height)
{
	if (_device != nullptr)
		_device->release();
	_device = std::make_unique<dx11::device>();
	return _device->initialize(hwnd, width, height);
}

void dotth::renderer::draw(void)
{
	if (_device == nullptr)
		return;

	_device->draw_begin();

	while (_queue.empty() == false)
	{
		if (auto p = _queue.front())
			p->draw();
		_queue.pop();
	}

	_device->draw_end();
}
