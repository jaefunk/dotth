#include "Scene.h"
#include "curl.h"
#pragma comment(lib, "libcurl/lib/Win64/libcurl.lib")

size_t writeFunction(void *ptr, size_t size, size_t nmemb, std::string* data) {
	data->append((char*)ptr, size * nmemb);
	return size * nmemb;
}

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
}
