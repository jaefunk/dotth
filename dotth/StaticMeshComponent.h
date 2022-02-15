#pragma once

#include "MeshComponent.h"
#include "StaticMesh.h"
#include "Material.h"

class StaticMeshComponent : public MeshComponent
{
public:
	std::shared_ptr<Material> material{ new Material };
	std::shared_ptr<StaticMesh> mesh{ new StaticMesh };

public:
	virtual void OnInit(void) override;
	virtual void OnUpdate(void) override;
	virtual void OnDraw(void) override;
	virtual void OnDestroy(void) override;
};