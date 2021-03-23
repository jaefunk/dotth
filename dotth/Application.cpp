#include "Application.h"

bool Application::Loop()
{
	Scenario::Instance()->Loop();
	_RHI.Draw();
	return true;
}
