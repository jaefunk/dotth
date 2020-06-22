
#pragma once

#include "framework/scene.h"
#include "graphics/drawable.h"

class TestScene : public scene
{
public:
	virtual void on_init(void) override 
	{
		camera::get()->set_at(DirectX::XMFLOAT3(0.f, 0.f, 0.f));
		camera::get()->set_up(DirectX::XMFLOAT3(0.f, 1.f, 0.f));
		camera::get()->set_eye(DirectX::XMFLOAT3(0.f, 0.f, -10.f));
		camera::get()->set_fov(DirectX::XM_PI * 0.25f);
		camera::get()->set_near(0.1f);
		camera::get()->set_far(1000.f);

		auto p = std::make_shared<drawable>();
		p->name("triangle");
		attach(p);
	}
	virtual void on_update(void) override 
	{
	};
	virtual void on_render(void) override
	{
	};
};
