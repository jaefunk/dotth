#include "EntryPoint.h"
#include "SampleObject.h"

void EntryPoint::OnInit(void)
{
	SetCameraPosition(Float3(0.f, 90.f, -400.f));
	SetCameraLookAt(Float3(0.f, 90.f, 0.f));
	SetCameraUp(Float3(0.f, 1.f, 0.f));
	SetCameraFrustumFieldOfView(3.141592f * 0.25f);
	SetCameraFrustumNearFieldDistance(0.1f);
	SetCameraFrustumFarFieldDistance(1000.f);
	
	std::shared_ptr<SampleObject> A = std::make_shared<SampleObject>();
	A->Rename("A");
	SpawnObject(A);


	std::shared_ptr<SampleObject> B = std::make_shared<SampleObject>();
	B->Rename("B");
	B->Scaling(0.5f);
	B->TranslateX(100.f);

	A->AddChild(B);
}

void EntryPoint::OnDestroy(void)
{
}

void EntryPoint::OnUpdate(void)
{
	
}

void EntryPoint::OnDraw(void)
{
}