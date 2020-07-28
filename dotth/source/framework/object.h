#pragma once

#include "Framework/Node.h"
#include "Framework/Component.h"

class Object : public Node<Object>
{
	friend Component;
public:
	void Init(void)
	{
		OnInit();
		std::for_each(_Components.begin(), _Components.end(), [](std::shared_ptr<Component> Component) {
			Component->OnInit();
		});
		Foreach([](std::shared_ptr<Object> child) {
			child->Init();
		});
	}
	void Update(void)
	{
		OnUpdate();
		std::for_each(_Components.begin(), _Components.end(), [](std::shared_ptr<Component> Component) {
			Component->OnUpdate();
		});
		Foreach([](std::shared_ptr<Object> child) {
			child->Update();
		});
	}
	void Draw(void)
	{
		OnDraw();
		std::for_each(_Components.begin(), _Components.end(), [](std::shared_ptr<Component> Component) {
			Component->OnDraw();
		});
		Foreach([](std::shared_ptr<Object> child) {
			child->Draw();
		});
	}
	void Destroy(void)
	{
		OnDestroy();
		std::for_each(_Components.begin(), _Components.end(), [](std::shared_ptr<Component> Component) {
			Component->OnDestroy();
		});
		Foreach([](std::shared_ptr<Object> child) {
			child->Destroy();
		});
	}

protected:
	virtual void OnInit(void) {};
	virtual void OnUpdate(void) {};
	virtual void OnDraw(void) {};
	virtual void OnDestroy(void) {};

private:
	std::list<std::shared_ptr<Component>> _Components;
public:
	void AttachComponent(std::shared_ptr<Component> target, std::string name = std::string())
	{
		if (_Components.end() != std::find(_Components.begin(), _Components.end(), target))
			return;
		target->_Owner = this->shared_from_this();
		_Components.push_back(target);
	}

	void DetachComponent(std::shared_ptr<Component> target)
	{
		target->_Owner = nullptr;
		_Components.remove(target);
	}

	template <typename ty>
	std::shared_ptr<ty> FindComponent(void)
	{
		for (const auto& comp : _Components)
		{
			if (auto casted = std::dynamic_pointer_cast<ty>(comp))
				return casted;
		}
		return nullptr;
	}
};
