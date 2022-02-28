#pragma once

#include "Scene.h"

class EntryPoint : public Scene
{
public:
	virtual void OnInit(void) override;
	//virtual void OnDestroy(void) override;
	virtual void OnUpdate(void) override;
	//virtual void OnDraw(void) override;
	//virtual void OnDrawImGui(void) override;

private:
	std::shared_ptr<Object> obj;
};