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
	if (_SceneStack.empty() == true)
		return;
	if (_SceneChanged == false)
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

void Scenario::Loop(void)
{
	printf("LOOP: ");
	ApplyNewScene();
	if (_CurrentScene == nullptr)
		return;
	_CurrentScene->Update();
	_CurrentScene->Draw();
	printf("\n");
}
