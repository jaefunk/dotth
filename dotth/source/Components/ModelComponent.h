
#pragma once

#include "Framework/Component.h"

class ModelComponent : public Component
{
public:
	virtual void OnInit(void);
	virtual void OnUpdate(void);
	virtual void OnDraw(void);
	virtual void OnDestroy(void);
};