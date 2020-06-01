
#pragma once

#include "framework/scene.h"
#include "graphics/drawable.h"

class TestScene : public dotth::scene
{
public:
	TestScene(void)
	{
	}
	virtual void on_init(void) override 
	{
		auto p = std::make_shared<dotth::object>();
		p->init();
		attach(p);
	}
	virtual void on_update(void) override 
	{
	};
};
