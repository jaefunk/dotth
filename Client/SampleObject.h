
#pragma once

#include "StaticMeshComponent.h"
#include "SkeletalMeshComponent.h"

#include "Object.h"

class SampleObject : public Object
{
private:
	std::shared_ptr<SkeletalMeshComponent> skeletalMeshComponent;

protected:
	virtual void OnInit(void) override;
	virtual void OnDestroy(void) override;
	virtual void OnUpdate(void) override;
	virtual void OnDraw(void) override;
	virtual void OnDrawImGui(void) override;
};