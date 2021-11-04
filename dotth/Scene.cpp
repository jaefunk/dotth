#include "Scene.h"
#include "D3D11RHI.h"

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
		Obj->Update(DeltaSeconds);
	}
	D3D11RHI::Camera()->Sync();
	for (std::shared_ptr<Object> Obj : Objects)
	{
		Obj->UpdateTransform();
	}
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

void Scene::SetCameraPosition(const Vector3& value)
{
	D3D11RHI::Camera()->SetEye(value);
}
void Scene::SetCameraUp(const Vector3& value)
{
	D3D11RHI::Camera()->SetUp(value);
}
void Scene::SetCameraLookAt(const Vector3& value)
{
	D3D11RHI::Camera()->SetAt(value);
}
void Scene::SetCameraViewportSize(int width, int height)
{
	D3D11RHI::Camera()->SetViewportSize(width, height);
}
void Scene::SetCameraFrustumFieldOfView(float radian)
{
	D3D11RHI::Camera()->SetFieldOfView(radian);
}
void Scene::SetCameraFrustumNearFieldDistance(float value)
{
	D3D11RHI::Camera()->SetNear(value);
}
void Scene::SetCameraFrustumFarFieldDistance(float value)
{
	D3D11RHI::Camera()->SetFar(value);
}

void Scene::DrawImGui(void)
{
	OnDrawImGui();
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