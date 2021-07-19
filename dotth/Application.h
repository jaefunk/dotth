
#pragma once

#include "Scenario.h"
#include "D3D11RHI.h"
#include "ResourceManager.h"

#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_win32.h"
#include "imgui/backends/imgui_impl_dx11.h"

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
};

template<typename SceneTy>
void Application::Initialize(const Configuration & config)
{
	assert(config.Validation());
	ResourceManager::Instance()->Initialize();
	ResourceManager::Instance()->Load("reserved.json");
	D3D11RHI::Initialize(config.Hwnd, config.Width, config.Height);
	Scenario::Instance()->Assign<SceneTy>("entrypoint");
	Scenario::Instance()->Push("entrypoint");


	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplWin32_Init(config.Hwnd);
	ImGui_ImplDX11_Init(D3D11RHI::Device(), D3D11RHI::Context());
}
