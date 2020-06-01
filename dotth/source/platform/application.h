
#pragma once

#include "../utility/utility.h"
#include "../framework/scene.h"
#include "../graphics/renderer.h"

namespace dotth 
{
	class application 
	{
	private:
		utility::timer _timer;
		scenario _scenario;
		renderer _renderer;
	public:
		bool init_application(void);
		scenario* get_scenario(void) 
		{
			return &_scenario;
		}
		renderer* get_renderer(void) 
		{
			return &_renderer;
		}
		bool init_scenario(std::shared_ptr<scene> root_scene, std::string key)
		{
			_scenario.assign_scene<dotth::scene>(key);
			_scenario.push(key);
			return false;
		}
		bool init_renderer(HWND hwnd, int width, int height);
		bool loop(void);
	};
}