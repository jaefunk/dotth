#include "EntryPoint.h"
#include "SampleObject.h"

void EntryPoint::OnInit(void)
{
	SetCameraPosition(Float3(0.f, 0.f, -9.f));
	SetCameraLookAt(Float3(0.f, 0.f, 0.f));
	SetCameraUp(Float3(0.f, 1.f, 0.f));
	SetCameraFrustumFieldOfView(PI * 0.25f);
	SetCameraFrustumNearFieldDistance(0.1f);
	SetCameraFrustumFarFieldDistance(1000.f);
	
	
	std::shared_ptr<SampleObject> so = std::make_shared<SampleObject>();
	SpwanObject(so);
}

void EntryPoint::OnDestroy(void)
{
}

void EntryPoint::OnUpdate(void)
{
	static float f = 0.f;
	static float d = 0.05f;
	f += d;
	if (abs(f) > 3.f)
		d *= -1;

	SetCameraLookAt(Float3(f, 0.f, 0.f));
}

void EntryPoint::OnDraw(void)
{
}