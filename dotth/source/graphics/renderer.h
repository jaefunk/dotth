
#pragma once

#include "../dotth.h"
#include "dx11/dx11_device.h"

namespace dotth 
{
	class drawable;
	class renderer
	{
	private:
		std::unique_ptr<dotth::dx11> _device;
		std::queue<dotth::drawable*> _queue;

	public:
		void enqueue(dotth::drawable* pd)
		{
			_queue.push(pd);
		}		

	public:
		bool initialize(HWND hwnd, int width, int height);
		void draw(void);
	};
}