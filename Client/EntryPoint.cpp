#include "EntryPoint.h"
#include "SampleObject.h"
#include "StaticMeshComponent.h"
#include "SkeletalMeshComponent.h"
#include "Camera.h"
#include "../dotth/Math/Easing.h"

void EntryPoint::OnInit(void)
{
	//auto StaticMeshObject = std::make_shared<Object>();
	//StaticMeshObject->AddComponent<StaticMeshComponent>();
	//StaticMeshObject->Translate(Vector3(-100.f, 0.f, 0.f));
	//SpawnObject(StaticMeshObject);

	auto SkeletalMeshObject = std::make_shared<Object>();
	SkeletalMeshObject->AddComponent<SkeletalMeshComponent>();
	SkeletalMeshObject->Translate(Vector3(100.f, 0.f, 0.f));
	SpawnObject(SkeletalMeshObject);

	
	//GetActiveCamera()->GetCameraComponent()->SetEye(Vector3(0.f, 50.f, -1200.f));
	GetActiveCamera()->GetCameraComponent()->SetUp(Vector3::Up());
	//GetActiveCamera()->GetCameraComponent()->SetAt(Vector3(0.f, 50.f, 0.f));
}

void EntryPoint::OnUpdate(void)
{
	//static bool b = false;
	//static float f = 0.f;
	//if (f >= 1.f)
	//	b = false;
	//if (f <= 0.f)
	//	b = true;
	//if (b == true)
	//	f += GetDeltaSeconds();
	//else 
	//	f -= GetDeltaSeconds();
	//f = clamp(0.f, 1.f, f);
	//printf("%f\n", f);
	//float f2 = f;
	//FindObject("linear")->SetScale(Vector3((f2 * 1500.f) - 750.f , 0.f, 500.f));
	//float in = (easing::sin::out(f2) * 1500.f) - 750.f;
	//FindObject("in")->SetPosition(Vector3(in, 0.f, 400.f));
	//float out = (easing::quad::out(f2) * 1500.f) - 750.f;
	//FindObject("out")->SetPosition(Vector3(out, 0.f, 300.f));
	//float in_out = (easing::cubic::out(f2) * 1500.f) - 750.f;
	//FindObject("in_out")->SetPosition(Vector3(in_out, 0.f, 200.f));
}

//void EntryPoint::OnDraw(void)
//{
//}
//
//void EntryPoint::OnDrawImGui(void)
//{
//}
