#include "EntryPoint.h"
#include "SampleObject.h"
#include "staticMeshComponent.h"
#include "Camera.h"

void EntryPoint::OnInit(void)
{
	{
		auto so2 = std::make_shared<Object>();
		so2->Rename("so2");
		auto smc2 = so2->AddComponent<StaticMeshComponent>();
		smc2->Load2();
		so2->SetScale(Vector3(10.f));
		SpawnObject(so2);
	}
	
	auto so1 = std::make_shared<Object>();
	so1->Rename("so1");
	auto smc1 = so1->AddComponent<StaticMeshComponent>();
	smc1->Load1();
	SpawnObject(so1);
}

void EntryPoint::OnUpdate(void)
{
	static float f = 0.f;
	f += GetDeltaSeconds() * 3.141592f;
	float s = sin(f) * 300.f;
	float w = cos(f) * 300.f;
	FindObject("so1")->SetPosition(Vector3(s, 100.f, w));
	GetActiveCamera()->GetCameraComponent()->SetAt(FindObject("so1")->GetLocalPosition());
}

//void EntryPoint::OnDraw(void)
//{
//}
//
//void EntryPoint::OnDrawImGui(void)
//{
//}
