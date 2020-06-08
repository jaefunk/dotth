
#pragma once

#include "framework/scene.h"

class TestScene : public scene
{
public:
	TestScene(void)
	{
	}
	virtual void on_init(void) override 
	{
		auto p = std::make_shared<object>();
		p->init();
		attach(p);
	}
	virtual void on_update(void) override 
	{
	};
};
