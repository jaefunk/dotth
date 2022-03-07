#pragma once

#include "Base.h"

class Object;
class Component : public Base
{
private:
	std::weak_ptr<Base> Owner;

public:
	void SetOwner(std::weak_ptr<Base> owner)
	{
		Owner = owner;
	}
	
	template <typename CastTy = Object>
	std::shared_ptr<CastTy> GetOwner(void)
	{
		return std::dynamic_pointer_cast<CastTy>(Owner.lock());
	}

public:
	virtual void OnInit(void);
	virtual void OnUpdate(void);
	virtual void OnLateUpdate(void);
	virtual void OnDraw(void);
	virtual void OnDestroy(void);
	virtual void OnDrawImGui(void);
};
