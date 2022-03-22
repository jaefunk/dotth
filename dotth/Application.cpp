#include "Application.h"

void Application::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (ImGui_ImplWin32_WndProcHandler(hWnd, message, wParam, lParam))
		return;
	
	static POINT p;
	GetCursorPos(&p);
	ScreenToClient(hWnd, &p);
	InputSystem::Instance()->UpdateMouseCursorPosition(p.x, p.y);

	switch (message)
	{
	case WM_KEYDOWN:
	case WM_KEYUP:
	case WM_LBUTTONDOWN:
	case WM_LBUTTONUP: 
	case WM_LBUTTONDBLCLK: 
	case WM_RBUTTONDOWN:
	case WM_RBUTTONUP:
	case WM_RBUTTONDBLCLK:
	case WM_MBUTTONDOWN:
	case WM_MBUTTONUP:
		InputSystem::Instance()->PushBuffer(message, wParam, lParam);
		break;
	}
}

bool Application::Loop()
{	
	InputSystem::Instance()->ArrangeBuffer();
	InputSystem::Instance()->BroadcastEvent();
	Scenario::Instance()->Update();
	InputSystem::Instance()->ReleaseBuffer();

	D3D11RHI::StandbyDeferred();
	Scenario::Instance()->Draw();
	D3D11RHI::Draw();
	
	D3D11RHI::BeginImGui();
	Scenario::Instance()->DrawImGui();
	D3D11RHI::EndImGui();

	D3D11RHI::Present();

	return true;
}
