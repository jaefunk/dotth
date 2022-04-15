
#include "PrimitiveTestScene.h"
#include "Camera.h"
#include "Primitive.h"

void PrimitiveTestScene::OnInit(void)
{
	static float eye[3] = { 0.f, 0.f, -2.f };
	GetActiveCamera()->GetCameraComponent()->SetEye(dotth::vector3(eye));
	//SpawnObject<Triangle>();
	//SpawnObject<Square>();
	SpawnObject<Cube>();
	//SpawnObject<Plane>(20);
}

void PrimitiveTestScene::OnUpdate(void)
{
}

void PrimitiveTestScene::OnDrawImGui(void)
{
	ImGui::Begin("EntryPoint");
	{
		static float eye[3] = { 0.f, 0.f, -2.f };
		if (ImGui::DragFloat3("eye", eye, 1.f, -1000.f, 1000.f, "%f"))
		{
			GetActiveCamera()->GetCameraComponent()->SetEye(dotth::vector3(eye));
		}

		static float at[3] = { 0.f, 0.f, 0.f };
		if (ImGui::DragFloat3("at", at, 1.f, -1000.f, 1000.f, "%f"))
		{
			GetActiveCamera()->GetCameraComponent()->SetAt(dotth::vector3(at));
		}

		static float fov = 90.f;
		if (ImGui::DragFloat("fov", &fov, 1.f, 0.f, 180.f, "%f"))
		{
			float jj = (fov / 180.f) * 3.141592f;
			GetActiveCamera()->GetCameraComponent()->SetFieldOfView(jj);
		}
	}
	ImGui::End();
}
