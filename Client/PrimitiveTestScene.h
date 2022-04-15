#pragma once

#include "Scene.h"

class PrimitiveTestScene : public Scene
{
public:
	virtual void OnInit(void) override;
	virtual void OnUpdate(void) override;
	virtual void OnDrawImGui(void) override;
};