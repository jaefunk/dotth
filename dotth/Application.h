
#pragma once

#include "Scenario.h"
#include "D3D11RHI.h"

struct Configuration
{
	HWND Hwnd;
	int Width;
	int Height;

	bool Validation(void) const
	{
		return true;
	}
};

class Application
{
public:
	template <typename SceneTy>
	void Initialize(const Configuration& config);
	bool Loop();
};

template<typename SceneTy>
void Application::Initialize(const Configuration & config)
{
	assert(config.Validation());
	D3D11RHI::Initialize(config.Hwnd, config.Width, config.Height);
	Scenario::Instance()->Assign<SceneTy>("entrypoint");
	Scenario::Instance()->Push("entrypoint");
}
