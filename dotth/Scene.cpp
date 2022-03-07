#include "Scene.h"
#include "D3D11RHI.h"
#include "Camera.h"

Scene::Scene(void)
{
	unsigned int width, height;
	D3D11RHI::GetViewportSize(width, height);
	ActiveCamera = SpawnObject<Camera>(width, height);
	ActiveCamera->Rename("MainCamera");
}

void Scene::Init(void)
{
	OnInit();
	for (std::shared_ptr<Object> Obj : Objects)
	{
		Obj->Init();
	}	
}

void Scene::Update(void)
{
	static std::chrono::system_clock::time_point BeforeFrameTimeStamp = std::chrono::system_clock::now();
	static std::chrono::system_clock::time_point CurrentFrameTimeStamp;
	CurrentFrameTimeStamp = std::chrono::system_clock::now();
	std::chrono::duration<float> TimeDiff = CurrentFrameTimeStamp - BeforeFrameTimeStamp;
	DeltaSeconds = TimeDiff.count();
	BeforeFrameTimeStamp = CurrentFrameTimeStamp;

	OnUpdate();
	for (std::shared_ptr<Object> Obj : Objects)
	{
		Obj->SetActiveCamera(ActiveCamera);
		Obj->Update(DeltaSeconds);
	}
	for (std::shared_ptr<Object> Obj : Objects)
	{
		Obj->UpdateTransform();
	}
	ActiveCamera->GetCameraComponent()->Sync();
}

void Scene::Draw(void)
{
	OnDraw();
	for (std::shared_ptr<Object> Obj : Objects)
	{
		Obj->Draw();
	}
}

void Scene::Destroy(void)
{
	OnDestroy();
	for (std::shared_ptr<Object> Obj : Objects)
	{
		Obj->Destroy();
	}
}

void Scene::SpawnObject(std::shared_ptr<Object> object)
{
	// verify unique...
	for (std::shared_ptr<Object> Obj : Objects)
	{
		if (Obj->GetSerial() == object->GetSerial())
		{
			return;
		}
	}

	Objects.push_back(object);
}

void Scene::RemoveObject(std::shared_ptr<Object> object)
{
	object->Destroy();
	Objects.remove(object);
}

std::shared_ptr<class Camera> Scene::GetActiveCamera(void)
{
	return ActiveCamera;
}

float Scene::GetDeltaSeconds(void)
{
	return DeltaSeconds;
}

void Scene::DrawImGui(void)
{
	//OnDrawImGui();
	//for (auto obj : Objects)
	//{
	//	obj->DrawImGui();
	//}
}

void Scene::DrawImGuiHierarchy(void)
{
	ImGui::Begin("Hierarchy");
	for (auto obj : Objects)
	{
		obj->DrawImGuiHierarchy();
	}
	ImGui::End();
}