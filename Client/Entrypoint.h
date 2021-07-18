#pragma once

#include "Scene.h"

class EntryPoint : public Scene
{
public:
	virtual void OnInit(void) override;
	virtual void OnDestroy(void) override;
	virtual void OnUpdate(void) override;
	virtual void OnDraw(void) override;

private:
	std::shared_ptr<Object> o1;
	std::shared_ptr<Object> o2;
};