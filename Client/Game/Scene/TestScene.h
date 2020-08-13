
#pragma once

#include "Framework/Scene.h"
#include "framework/sample_object.h"

class TestScene : public Scene
{
public:
	virtual void OnInit(void) override 
	{
		Camera::Instance()->SetAt(DirectX::XMFLOAT3(0.f, 0.f, 0.f));
		Camera::Instance()->SetUp(DirectX::XMFLOAT3(0.f, 1.f, 0.f));
		Camera::Instance()->SetEye(DirectX::XMFLOAT3(7.f, 8.f, -9.f));
		Camera::Instance()->SetFieldOfView(DirectX::XM_PI * 0.25f);
		Camera::Instance()->SetNear(0.1f);
		Camera::Instance()->SetFar(1000.f);

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
