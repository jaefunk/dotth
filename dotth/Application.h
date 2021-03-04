
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
	D3D11RHI _RHI;

	template <typename SceneTy>
	void Initialize(const Configuration& config)
	{
		assert(config.Validation());
		_RHI.Initialize(config.Hwnd, config.Width, config.Height);
		Scenario::Instance()->Assign<SceneTy>("entrypoint");
		Scenario::Instance()->Push("entrypoint");
	}

	bool Loop()
	{
		Scenario::Instance()->Loop();
		_RHI.Draw();
		return true;
	}



	LRESULT WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		return ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam);
	}

};

