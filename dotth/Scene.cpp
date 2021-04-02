#include "Scene.h"

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
}

void Scene::Draw(void)
{
	OnDraw();
	for (std::shared_ptr<Object> Obj : _Objects)
	{
		Obj->Draw();
	}
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
