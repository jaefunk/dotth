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
	so->GetTransform().TranslateY(2.f);
	std::shared_ptr<SampleObject> so2 = std::make_shared<SampleObject>();
	so2->Rename("A");
	SpwanObject(so2);
	
}

void EntryPoint::OnDestroy(void)
{
}

void EntryPoint::OnUpdate(void)
{
	FindObject("A")->GetTransform().RotateYaw(0.01f);
}

void EntryPoint::OnDraw(void)
{
}