#include "Scene.h"
#include "D3D11RHI.h"

void Scene::Init(void)
{
	OnInit();
	for (std::shared_ptr<Object> Obj : _Objects)
	{
		Obj->Init();
	}	
}

void Scene::Update(void)
{
	OnUpdate();
	for (std::shared_ptr<Object> Obj : _Objects)
	{
		Obj->Update();
	}
	D3D11RHI::Camera()->Sync();
	for (std::shared_ptr<Object> Obj : _Objects)
	{
		Obj->UpdateTransform();
	}
	for (std::shared_ptr<Object> Obj : _Objects)
	{
		Obj->LateUpdate();
	}
}

void Scene::Draw(void)
{
	OnDraw();
	for (std::shared_ptr<Object> Obj : _Objects)
	{
		Obj->Draw();
	}
}

void Scene::DrawImGui(void)
{
	OnDrawImGui();
}

void Scene::Destroy(void)
{
	OnDestroy();
	for (std::shared_ptr<Object> Obj : _Objects)
	{
		Obj->Destroy();
	}
}

void Scene::OnInit(void) 
{
}

void Scene::OnUpdate(void) 
{
}

void Scene::OnDraw(void) 
{
}

void Scene::OnDestroy(void) 
{
}

void Scene::SpawnObject(std::shared_ptr<Object> object)
{
	for (std::shared_ptr<Object> Obj : _Objects)
	{
		if (object->Serial() == Obj->Serial())
		{
			return;
		}
	}
	_Objects.push_back(object);
}

void Scene::RemoveObject(std::shared_ptr<Object> object)
{
	_Objects.remove(object);
}

void Scene::SetCameraPosition(const Float3& value)
{
	D3D11RHI::Camera()->SetEye(value);
}
void Scene::SetCameraUp(const Float3& value)
{
	D3D11RHI::Camera()->SetUp(value);
}
void Scene::SetCameraLookAt(const Float3& value)
{
	D3D11RHI::Camera()->SetAt(value);
}
void Scene::SetCameraViewportSize(const int& width, const int& height)
{
	D3D11RHI::Camera()->SetViewportSize(width, height);
}
void Scene::SetCameraFrustumFieldOfView(const float& radian)
{
	D3D11RHI::Camera()->SetFieldOfView(radian);
}
void Scene::SetCameraFrustumNearFieldDistance(const float& value)
{
	D3D11RHI::Camera()->SetNear(value);
}
void Scene::SetCameraFrustumFarFieldDistance(const float& value)
{
	D3D11RHI::Camera()->SetFar(value);
}

void Scene::DrawImGuiHierarchy(void)
{
	ImGui::Begin("Hierarchy");
	for (auto obj : _Objects)
	{
		obj->DrawImGuiHierarchy();
	}
	ImGui::End();
}