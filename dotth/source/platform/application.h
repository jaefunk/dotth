
#pragma once

#include "utility/utility.h"
#include "Framework/Scenario.h"
#include "graphics/renderer.h"
#include "Graphics/RHI/DynamicRHI.h"
namespace dotth 
{
	class application 
	{
	private:

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
		bool init_renderer(void* handle, int width, int height);
		bool loop(void);

		void Quit(void)
		{

		}
	};
}