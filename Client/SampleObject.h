
#pragma once

#include "Object.h"

class SampleObject : public Object
{
public:
	SampleObject(void);

protected:
	virtual void OnInit(void) override;
	virtual void OnDestroy(void) override;
	virtual void OnUpdate(void) override;
	virtual void OnDraw(void) override;

private:
	std::shared_ptr<class StaticMeshComponent> _StaticMesh;
};