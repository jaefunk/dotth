#include "Scenario.h"

void Scenario::Push(std::string key)
{
	_SceneStack.push(key);
	_SceneChanged = true;
}

void Scenario::Pop(void)
{
	if (_SceneStack.size() <= 1)
		return;
	_SceneStack.pop();
	_SceneChanged = true;
}

void Scenario::ApplyNewScene(void)
{
	if (_SceneChanged == false)
		return;
	if (_SceneStack.empty() == true)
		return;
	_SceneChanged = false;
	auto iterator = _SignedScene.find(_SceneStack.top());
	if (iterator == std::end(_SignedScene))
		return;
	if (_CurrentScene != nullptr)
		_CurrentScene->Destroy();
	_CurrentScene = iterator->second();
	_CurrentScene->Init();
}

void Scenario::Update(void)
{
	ApplyNewScene();
	if (_CurrentScene == nullptr)
		return;
	_CurrentScene->Update();
}

void Scenario::Draw(void)
{
	_CurrentScene->Draw();
}

void Scenario::DrawImGui(void)
{
	_CurrentScene->DrawImGuiHierarchy();
	_CurrentScene->DrawImGui();
}
