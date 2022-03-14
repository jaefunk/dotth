#pragma once

#include "Scene.h"



class EntryPoint : public Scene
{
public:
	class AnimationController* animationController;
	virtual void OnInit(void) override;
	//virtual void OnDestroy(void) override;
	virtual void OnUpdate(void) override;
	//virtual void OnDraw(void) override;
	virtual void OnDrawImGui(void) override;
};