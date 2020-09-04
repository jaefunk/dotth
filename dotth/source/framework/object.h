#pragma once

#include "Framework/Node.h"
#include "Framework/Component.h"

class Object : public Node<Object>
{
	friend Component;
public:
	void Init(void);
	void Update(void);
	void Draw(void);
	void Destroy(void);

protected:
	virtual void OnInit(void);;
	virtual void OnUpdate(void);;
	virtual void OnDraw(void);;
	virtual void OnDestroy(void);;

private:
	std::list<std::shared_ptr<Component>> _Components;
public:
	void AttachComponent(std::shared_ptr<Component> target, std::string name = std::string());
	void DetachComponent(std::shared_ptr<Component> target);

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
