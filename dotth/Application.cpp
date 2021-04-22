#include "Application.h"

bool Application::Loop()
{
	D3D11RHI::PreDraw();
	Scenario::Instance()->Loop();
	D3D11RHI::PostDraw();

	return true;
}
