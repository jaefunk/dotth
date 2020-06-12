
#pragma once

#include "framework/scene.h"
#include "graphics/drawable.h"

class TestScene : public scene
{
public:
	TestScene(void)
	{
	}
	virtual void on_init(void) override 
	{
		auto p = std::make_shared<drawable>();
		attach(p);
	}
	virtual void on_update(void) override 
	{
	};
	virtual void on_render(void) override
	{
	};
};
