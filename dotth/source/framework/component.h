#pragma once

#include "Framework/Base.h"

class Object;
class Component : public Base
{
	friend Object;
private:
	std::shared_ptr<Object> _Owner;

public:
	std::shared_ptr<Object> GetOwner(void);

public:
	virtual void OnInit(void) {};
	virtual void OnUpdate(void) {};
	virtual void OnDraw(void) {};
	virtual void OnDestroy(void) {};
};
