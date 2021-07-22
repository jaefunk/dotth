#include "Application.h"

void Application::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (ImGui_ImplWin32_WndProcHandler(hWnd, message, wParam, lParam))
		return;

	switch (message)
	{
	case WM_KEYDOWN:
		//printf("%lld key down %llu\n", wParam, lParam);
		break;
		//case WM_CHAR:
		//	printf("b\n");
		//	break;
	case WM_KEYUP:
		//printf("%lld key up %llu\n", wParam, lParam);
		break;
	case WM_MOUSEMOVE: 
		//printf("%lld mousemove %llu\n", wParam, lParam);
		break;
	case WM_LBUTTONDOWN: break;
	case WM_LBUTTONUP: break;
	case WM_LBUTTONDBLCLK: break;
	case WM_RBUTTONDOWN: break;
	case WM_RBUTTONUP: break;
	case WM_RBUTTONDBLCLK: break;
	case WM_MBUTTONDOWN: break;
	case WM_MBUTTONUP: break;
		break;
	}
	//printf("message: %d %lld %llu\n", message, wParam, lParam);
}

bool Application::Loop()
{	
	Scenario::Instance()->Update();

	D3D11RHI::StandbyDeferred();
	Scenario::Instance()->Draw();
	D3D11RHI::Draw();
	D3D11RHI::BeginImGui();
	Scenario::Instance()->DrawImGui();
	//static bool b = true;
	//ImGui::ShowDemoWindow(&b);
	D3D11RHI::EndImGui();
	D3D11RHI::Present();
	return true;
}
