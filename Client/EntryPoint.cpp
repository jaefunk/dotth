#include "EntryPoint.h"
#include "SampleObject.h"
#include "../dotth/StaticMeshComponent.h"

void EntryPoint::OnInit(void)
{
	SetCameraPosition(Float3(0.f, 0, -300.f));
	SetCameraLookAt(Float3(0.f, 0, 0.f));
	SetCameraUp(Float3(0.f, 1.f, 0.f));
	SetCameraFrustumFieldOfView(3.141592f * 0.25f);
	SetCameraFrustumNearFieldDistance(0.1f);
	SetCameraFrustumFarFieldDistance(1000.f);
	
	std::shared_ptr<SampleObject> A = std::make_shared<SampleObject>();
	auto smc = A->AddComponent<StaticMeshComponent>();
	smc->Load1();
	SpawnObject(A);
	A->TranslateX(-70.f);

	std::shared_ptr<SampleObject> B = std::make_shared<SampleObject>();
	auto smc2 = B->AddComponent<StaticMeshComponent>();
	smc2->Load2();
	SpawnObject(B);
	B->TranslateX(70.f);


	//std::shared_ptr<SampleObject> B = std::make_shared<SampleObject>();
	//B->Rename("B");
	//B->Scaling(0.5f);
	//B->TranslateX(100.f);

	//A->AddChild(B);
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