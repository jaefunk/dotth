#include "EntryPoint.h"
#include "SampleObject.h"
#include "staticMeshComponent.h"
#include "Camera.h"
#include "../dotth/Math/Easing.h"

void EntryPoint::OnInit(void)
{
	{
		//auto so2 = std::make_shared<Object>();
		//so2->Rename("so2");
		//auto smc2 = so2->AddComponent<StaticMeshComponent>();
		//smc2->Load2();
		//so2->SetScale(Vector3(10.f));
		//SpawnObject(so2);
	}
	
	{
		//{
		//	auto so1 = std::make_shared<Object>();
		//	so1->Rename("linear");
		//	auto smc1 = so1->AddComponent<StaticMeshComponent>();
		//	smc1->Load1();
		//	SpawnObject(so1);
		//	so1->Translate(Vector3(-100.f, 0.f, 0.f));
		//}

		{
			auto so1 = std::make_shared<Object>();
			so1->Rename("linear");
			auto smc1 = so1->AddComponent<SkeletalMeshComponent>();
			smc1->Load();
			SpawnObject(so1);
			so1->Translate(Vector3(100.f, 0.f, 0.f));
		}
	}

	//{
	//	auto so1 = std::make_shared<Object>();
	//	so1->Rename("in");
	//	auto smc1 = so1->AddComponent<StaticMeshComponent>();
	//	smc1->Load1();
	//	SpawnObject(so1);
	//}

	//{
	//	auto so1 = std::make_shared<Object>();
	//	so1->Rename("out");
	//	auto smc1 = so1->AddComponent<StaticMeshComponent>();
	//	smc1->Load1();
	//	SpawnObject(so1);
	//}

	//{
	//	auto so1 = std::make_shared<Object>();
	//	so1->Rename("in_out");
	//	auto smc1 = so1->AddComponent<StaticMeshComponent>();
	//	smc1->Load1();
	//	SpawnObject(so1);
	//}
	
	GetActiveCamera()->GetCameraComponent()->SetEye(Vector3(0.f, 100.f, -400.f));
	GetActiveCamera()->GetCameraComponent()->SetUp(Vector3::Up());
	/*GetActiveCamera()->GetCameraComponent()->SetAt(Vector3::Zero());*/
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
