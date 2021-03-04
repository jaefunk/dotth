#pragma once

//#include "../dotth/Scene.h"
#include "Scene.h"

class EntryPoint : public Scene
{
public:
	virtual void OnInit(void) override;
	virtual void OnDestroy(void) override;
	virtual void OnUpdate(void) override;
	virtual void OnDraw(void) override;
};