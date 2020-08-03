#pragma once

#include "Framework/Base.h"

class Object;
class Component : public Base
{
	friend Object;
private:
	Object* _Owner;

public:
	const Object* GetOwner(void);

public:
	virtual void OnInit(void) {};
	virtual void OnUpdate(void) {};
	virtual void OnDraw(void) {};
	virtual void OnDestroy(void) {};
};
