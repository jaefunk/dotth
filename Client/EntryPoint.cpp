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
	//o1->RotatePitch(DirectX::XMConvertToRadians(90.f));
	auto smc1 = o1->AddComponent<StaticMeshComponent>();
	o1->SetScale(Vector3F(10.f, 1.f, 10.f));
	smc1->Load2();
	SpawnObject(o1);

	//o2 = std::make_shared<SampleObject>();
	//SpawnObject(o2);
	//for (auto i = 0; i < 4; ++i)
	//{
	//	for (auto j = 0; j < 4; ++j)
	//	{
	//		auto o = std::make_shared<SampleObject>();
	//		auto smc = o->AddComponent<StaticMeshComponent>();
	//		smc->Load1();
	//		o2->AddChild(o);
	//		o->TranslateX(-150.f + (j * 100));
	//		o->TranslateZ(-150.f + (i * 100));
	//		o->TranslateY(40.f);
	//	}
	//}
}

void EntryPoint::OnDestroy(void)
{
}

void EntryPoint::OnUpdate(void)
{
	//static float a = 0.f;
	//a += 0.101f;
	////static float r = 800.f;
	////float x = cos(a) * r;
	////float z = sin(a) * r;
	//SetCameraPosition(Float3(0.f, 300.f + a, -500.f));
	//SetCameraLookAt(Float3(0.f, 000.f + a, 0.f));
	//o2->RotateYaw(0.001f);
	
}

void EntryPoint::OnDraw(void)
{
}

void EntryPoint::OnDrawImGui(void)
{
	//bool show_demo_window = true;
	//if (show_demo_window)
	//	ImGui::ShowDemoWindow(&show_demo_window);
	//ImGui::Begin("test");
	//static float pitch = 0.f;
	//static float yaw = 0.f;
	//static float roll = 0.f;
	//ImGui::DragFloat("yaw", &yaw, 0.01f, 0.f, 3.14159f * 2.f, "%f", 1.f);
	//ImGui::DragFloat("pitch", &pitch, 0.01f, 0.f, 3.14159f * 2.f, "%f", 1.f);
	//ImGui::DragFloat("roll", &roll, 0.01f, 0.f, 3.14159f * 2.f, "%f", 1.f);
	//o2->SetRotation(Vector3F(pitch, yaw, roll));	
	//ImGui::End();
}
