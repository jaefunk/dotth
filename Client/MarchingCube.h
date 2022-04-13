
#pragma once

#include "Object.h"
#include "StaticMeshComponent.h"

class MarchingCube : public Object
{
public:
	MarchingCube(void);

public:
	virtual void OnInit(void) override;
	virtual void OnDestroy(void) override;
	virtual void OnUpdate(void) override;
	virtual void OnDraw(void) override;
	virtual void OnDrawImGui(void) override;

private:
	std::shared_ptr<StaticMeshComponent> staticMeshComponent;
};