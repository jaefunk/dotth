#include "EntryPoint.h"
#include "SampleObject.h"
#include "staticMeshComponent.h"



void EntryPoint::OnInit(void)
{
	SetCameraPosition(Float3(000.f, 500.f, -500.f));
	SetCameraLookAt(Float3(0.f, 000.f, 0.f));
	SetCameraUp(Float3(0.f, 1.f, 0.f));
	SetCameraFrustumFieldOfView(3.141592f * 0.3f);
	SetCameraFrustumNearFieldDistance(0.1f);
	SetCameraFrustumFarFieldDistance(100000.f);
	
	o1 = std::make_shared<SampleObject>();
	//auto smc2 = o1->AddComponent<StaticMeshComponent>();
	auto smc1 = o1->AddComponent<StaticMeshComponent>();
	//o1->SetScale(Vector3F(10.f, 1.f, 10.f));
	smc1->Load2();
	SpawnObject(o1);
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

void EntryPoint::OnDrawImGui(void)
{
}
