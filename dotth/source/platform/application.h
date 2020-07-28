
#pragma once

#include "utility/utility.h"
#include "Framework/Scenario.h"
#include "graphics/renderer.h"

namespace dotth 
{
	class application 
	{
	public:
		bool init_application(void);
		Scenario* get_scenario(void)
		{
			return Scenario::Instance();
		}
		renderer* get_renderer(void)
		{
			return renderer::Instance();
		}
		bool init_scenario(std::shared_ptr<Scene> root_scene, std::string key)
		{
			Scenario::Instance()->Assign<Scene>(key);
			Scenario::Instance()->Push(key);
			return false;
		}
		bool init_renderer(HWND hwnd, int width, int height);
		bool loop(void);
	};
}