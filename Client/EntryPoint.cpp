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
	


	std::shared_ptr<SampleObject> A = std::make_shared<SampleObject>();
	A->TranslateX(0.f);
	SpawnObject(A);
	
	std::shared_ptr<SampleObject> B = std::make_shared<SampleObject>();
	B->Rename("a");
	B->TranslateX(2.f);
	B->TranslateY(2.f);
	//A->Scaling(0.5f);
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