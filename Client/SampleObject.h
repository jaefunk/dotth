
#pragma once

#include "Object.h"

class SampleObject : public Object
{
protected:
	virtual void OnInit(void) override;
	virtual void OnDestroy(void) override;
	virtual void OnUpdate(void) override;
	virtual void OnDraw(void) override;
};