
#pragma once

#include "Scenario.h"

struct Configuration
{
	void* hwnd;
	int width;
	int height;

	bool Validation(void) const
	{
		return true;
	}
};

class Application
{
public:
	Application(const Configuration& config)
	{
		assert(config.Validation());
	}

	template <
		typename SceneTy, 
		typename = typename std::enable_if<std::is_base_of<Scene, SceneTy>::value, SceneTy>::type
	>
	void Initialize(void)
	{
		Scenario::Instance()->Assign<SceneTy>("entrypoint");
		Scenario::Instance()->Push("entrypoint");
	}

	bool Loop()
	{
		Scenario::Instance()->Loop();
		return true;
	}
};