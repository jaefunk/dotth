#include "EntryPoint.h"
#include "SampleObject.h"
#include "../dotth/StaticMeshComponent.h"

void EntryPoint::OnInit(void)
{
	SetCameraPosition(Float3(0.f, 0.f, -200.f));
	SetCameraLookAt(Float3(0.f, 0, 0.f));
	SetCameraUp(Float3(0.f, 1.f, 0.f));
	SetCameraFrustumFieldOfView(3.141592f * 0.3f);
	SetCameraFrustumNearFieldDistance(0.1f);
	SetCameraFrustumFarFieldDistance(1000.f);
	
	o1 = std::make_shared<SampleObject>();
	auto smc = o1->AddComponent<StaticMeshComponent>();
	smc->Load1();
	SpawnObject(o1);
	o1->TranslateX(-70.f);

	o2 = std::make_shared<SampleObject>();
	auto smc2 = o2->AddComponent<StaticMeshComponent>();
	smc2->Load2();
	SpawnObject(o2);
	o2->TranslateX(70.f);


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
	static float a = 0.f;
	a += 0.3f;
	SetCameraPosition(Float3(0.f, a, -200.f));
}

void EntryPoint::OnDraw(void)
{
}