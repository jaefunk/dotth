#pragma once

#include "PrimitiveComponent.h"

class MeshComponent : public PrimitiveComponent
{
public:
	virtual void OnInit(void) override;
	virtual void OnUpdate(void) override;
	virtual void OnDraw(void) override;
	virtual void OnDestroy(void) override;
};
