#pragma once

#include "Framework/Object.h"
#include "graphics/camera.h"

class Scene : public Base
{
	friend class Scenario;
private:
	std::shared_ptr<Object> _Root{ new Object };
	virtual void Init(void) 
	{
		OnInit();
		_Root->Init();
	};
	virtual void Update(void) 
	{
		OnUpdate();
		_Root->Update();
	};
	virtual void Draw(void) 
	{
		OnDraw();
		_Root->Draw();
	};
	virtual void Destroy(void) 
	{
		OnDestroy();
		_Root->Destroy();
	};

public:
	const std::shared_ptr<Object>& Root(void) {
		return _Root;
	}

public:
	virtual void OnInit(void) {};
	virtual void OnUpdate(void) {};
	virtual void OnDraw(void) {};
	virtual void OnDestroy(void) {};
};