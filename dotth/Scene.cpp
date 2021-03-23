#include "Scene.h"

void Scene::Init(void)
{
	OnInit();
	_Root->Init();
}

void Scene::Update(void)
{
	OnUpdate();
	_Root->Update();
}

void Scene::Draw(void)
{
	OnDraw();
	_Root->Draw();
}

void Scene::Destroy(void)
{
	OnDestroy();
	_Root->Destroy();
}

const std::shared_ptr<Object>& Scene::Root(void) {
	return _Root;
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
	nlohmann::json j;
	j["asdf"] = 10;
}
