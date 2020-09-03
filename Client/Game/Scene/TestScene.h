
#pragma once

#include "Framework/Scene.h"
#include "framework/sample_object.h"

class TestScene : public Scene
{
public:
	virtual void OnInit(void) override;
	virtual void OnUpdate(void) override;;
	virtual void OnDraw(void) override;;
};
