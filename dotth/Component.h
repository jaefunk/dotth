#pragma once

#include "Base.h"

class Object;
class Component : public Base
{
private:
	Base* Owner = nullptr;

public:
	void SetOwner(Base* inOwner)
	{
		Owner = inOwner;
	}
	
	template <typename CastTy = Object>
	CastTy* GetOwner(void)
	{
		return (CastTy*)Owner;
	}

public:
	virtual void OnInit(void);
	virtual void OnUpdate(void);
	virtual void OnLateUpdate(void);
	virtual void OnDraw(void);
	virtual void OnDestroy(void);
	virtual void OnDrawImGui(void);
};
