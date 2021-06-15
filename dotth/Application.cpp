#include "Application.h"

void Application::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
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
	D3D11RHI::PreDraw();
	Scenario::Instance()->Loop();
	D3D11RHI::PostDraw();
	return true;
}
