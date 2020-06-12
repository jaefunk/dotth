
#pragma once

#include "utility/utility.h"
#include "framework/scene.h"
#include "graphics/renderer.h"

namespace dotth 
{
	class application 
	{
	public:
		bool init_application(void);
		scenario* get_scenario(void)
		{
			return scenario::get();
		}
		renderer* get_renderer(void)
		{
			return renderer::get();
		}
		bool init_scenario(std::shared_ptr<scene> root_scene, std::string key)
		{
			scenario::get()->assign_scene<scene>(key);
			scenario::get()->push(key);
			return false;
		}
		bool init_renderer(HWND hwnd, int width, int height);
		bool loop(void);
	};
}