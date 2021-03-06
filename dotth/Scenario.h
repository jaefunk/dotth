#pragma once

#include "Scene.h"
#include "SingleInstance.h"

class Scenario : public SingleInstance<Scenario>
{
private:
	bool _SceneChanged = false;
	std::stack<std::string> _SceneStack;
	std::unordered_map<std::string, std::function<std::shared_ptr<Scene>(void)>> _SignedScene;
	std::shared_ptr<Scene> _CurrentScene;
	void ApplyNewScene(void);

public:
	void Push(std::string key);
	void Pop(void);
	void Loop(void);

public:
	template <typename SceneTy, typename = typename std::enable_if<std::is_base_of<Scene, SceneTy>::value, SceneTy>::type>
	void Assign(const std::string& key)
	{
		_SignedScene.insert({ key, []() { return std::make_shared<SceneTy>(); } });
	}
};