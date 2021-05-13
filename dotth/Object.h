#pragma once

#include "Node.h"
#include "Component.h"
#include "Math/Transform.h"

class Object : public Node<Object>
{
public:
	void Init(void);
	void Update(void);
	void Draw(void);
	void Destroy(void);

protected:
	virtual void OnInit(void);
	virtual void OnDestroy(void);
	virtual void OnUpdate(void);
	virtual void OnDraw(void);

private:
	Transform _Transform;
	std::list<std::shared_ptr<Component>> _Components;

public:
	Transform& GetTransform(void) { return _Transform; }
public:
	template <typename ty>
	std::shared_ptr<ty> AddComponent(void)
	{
		std::shared_ptr<ty> value = std::make_shared<ty>();
		value->SetOwner(this->shared_from_this());
		_Components.push_back(value);
		return value;
	}

	void AddComponent(std::shared_ptr<Component> component)
	{
		for (std::shared_ptr<Component> Comp : _Components)
		{
			if (Comp->Serial() == component->Serial())
			{
				return;
			}
		}
		_Components.push_back(component);
	}

	void RemoveComponent(std::shared_ptr<Component> component)
	{
		_Components.remove(component);
	}

	template <typename CastTy = Component>
	std::shared_ptr<CastTy> FindComponent(std::string name)
	{
		for (std::shared_ptr<Component> Comp : _Components)
		{
			if (Comp->Name() == name)
			{
				return std::dynamic_pointer_cast<CastTy>(Comp);
			}
		}
		return nullptr;
	}
};
