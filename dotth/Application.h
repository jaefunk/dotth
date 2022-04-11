
#pragma once

#include "Scenario.h"
#include "InputSystem.h"
#include "D3D11RHI.h"
#include "ResourceManager.h"
#include "LineRenderer.h"
#include "D3D11RHI2.h"

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
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	bool Loop();

private:
	D3D11RHI2 RHI;
};

template<typename SceneTy>
void Application::Initialize(const Configuration & config)
{
	assert(config.Validation());
	InputSystem::Instance()->Initialize();
	ResourceManager2::Instance()->Load();
	//RHI.Initialize(config.Hwnd, config.Width, config.Height);
	D3D11RHI::Initialize(config.Hwnd, config.Width, config.Height);
	D3D11RHI::InitializeImGui(config.Hwnd, config.Width, config.Height);
	LineRenderer::Instance()->Init();
	Scenario::Instance()->Assign<SceneTy>("entrypoint");
	Scenario::Instance()->Push("entrypoint");
}
