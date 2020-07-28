
#pragma once

#include "Framework/Scene.h"
#include "framework/sample_object.h"

class TestScene : public Scene
{
public:
	virtual void OnInit(void) override 
	{
		camera::get()->set_at(DirectX::XMFLOAT3(0.f, 0.f, 0.f));
		camera::get()->set_up(DirectX::XMFLOAT3(0.f, 1.f, 0.f));
		camera::get()->set_eye(DirectX::XMFLOAT3(0.f, 0.f, -10.f));
		camera::get()->set_fov(DirectX::XM_PI * 0.25f);
		camera::get()->set_near(0.1f);
		camera::get()->set_far(1000.f);

		auto p = std::make_shared<sample_object>();
		p->Name("triangle");
		Root()->Attach(p);
	}
	virtual void OnUpdate(void) override 
	{
	};
	virtual void OnDraw(void) override
	{
	};
};
