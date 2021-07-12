#pragma once

#include "Component.h"
#include "Object.h"

class PrimitiveComponent : public Component
{
public:
	virtual void OnInit(void) override;
	virtual void OnUpdate(void) override;
	virtual void OnDraw(void) override;
	virtual void OnDestroy(void) override;
};
