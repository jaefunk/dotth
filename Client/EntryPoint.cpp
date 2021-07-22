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

	o2 = std::make_shared<SampleObject>();
	SpawnObject(o2);
	for (auto i = 0; i < 4; ++i)
	{
		for (auto j = 0; j < 4; ++j)
		{
			auto o = std::make_shared<SampleObject>();
			auto smc = o->AddComponent<StaticMeshComponent>();
			smc->Load1();
			o2->AddChild(o);
			o->TranslateX(-150.f + (j * 100));
			o->TranslateZ(-150.f + (i * 100));
			o->TranslateY(40.f);
		}
	}
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
	o2->RotateYaw(0.001f);
	
}

void EntryPoint::OnDraw(void)
{
}

void EntryPoint::OnDrawImGui(void)
{
	if (ImGui::TreeNode("Outer size"))
	{
		static bool b = true;
		ImGui::Checkbox("visible", &b);
		if (ImGui::TreeNode("Outer size2"))
		{
			ImGui::Checkbox("visible", &b);
			ImGui::TreePop();
		}
		ImGui::TreePop();
	}


	ImGui::Begin("Hello, world!");
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	ImGui::Text("%f %f %f", o2->GetLocalRotation().x, o2->GetLocalRotation().y, o2->GetLocalRotation().z);
	static float f = 0.f;
	ImGui::DragFloat("test", &f, 1.f, 0.f, 1000.f, "%f", 1.f);
	o2->SetPosition(Vector3F(0.f, f, 0.f));
	ImGui::End();
}
