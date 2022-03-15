#pragma once

#include "MeshComponent.h"
#include "StaticMesh.h"
#include "Material.h"

class StaticMeshComponent : public MeshComponent
{
private:
	StaticMesh* staticMesh;
public:
	void SetStaticMesh(StaticMesh* inStaticMesh)
	{
		if (staticMesh != inStaticMesh)
			staticMesh = inStaticMesh;
	}

public:
	virtual void OnInit(void) override;
	virtual void OnUpdate(void) override;
	virtual void OnDraw(void) override;
	virtual void OnDestroy(void) override;
};