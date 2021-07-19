#include "Application.h"

void Application::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (ImGui_ImplWin32_WndProcHandler(hWnd, message, wParam, lParam))
		return;

	switch (message)
	{
	case WM_KEYDOWN:
		printf("%lld key down %llu\n", wParam, lParam);
		break;
		//case WM_CHAR:
		//	printf("b\n");
		//	break;
	case WM_KEYUP:
		printf("%lld key up %llu\n", wParam, lParam);
		break;
	case WM_MOUSEMOVE: 
		printf("%lld mousemove %llu\n", wParam, lParam);
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
	D3D11RHI::PreDraw();
	
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
	
    ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.
    ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    ImGui::End();
	ImGui::Render();
	
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	


	

	D3D11RHI::PostDraw();
	return true;
}
