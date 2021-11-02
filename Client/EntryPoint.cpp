#include "EntryPoint.h"
#include "SampleObject.h"
#include "staticMeshComponent.h"

void EntryPoint::OnInit(void)
{
	SetCameraPosition(Float3(000.f, 500.f, -500.f));
	SetCameraLookAt(Float3(0.f, 0.f, 0.f));
	SetCameraUp(Float3(0.f, 1.f, 0.f));
	SetCameraFrustumFieldOfView(3.141592f * 0.3f);
	SetCameraFrustumNearFieldDistance(0.1f);
	SetCameraFrustumFarFieldDistance(100000.f);
	
	auto so0 = std::make_shared<SampleObject>();
	auto smc0 = so0->AddComponent<StaticMeshComponent>();
	smc0->Load2();

	auto so1 = std::make_shared<SampleObject>();
	so1->TranslateX(50);
	auto smc1 = so1->AddComponent<StaticMeshComponent>();
	smc1->Load1();

	so0->Attach(so1);

	SpawnObject(so0);
}
//
//void EntryPoint::OnDestroy(void)
//{
//}
//
//void EntryPoint::OnUpdate(void)
//{
//}
//
//void EntryPoint::OnDraw(void)
//{
//}
//
//void EntryPoint::OnDrawImGui(void)
//{
//}
