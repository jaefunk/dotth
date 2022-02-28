#pragma once

#include "MeshComponent.h"
#include "StaticMesh.h"
#include "Material.h"

class StaticMeshComponent : public MeshComponent
{
private:
	std::shared_ptr<StaticMesh> mesh{ new StaticMesh };
	std::shared_ptr<Material> material{ new Material };

public:
	virtual void OnInit(void) override;
	virtual void OnUpdate(void) override;
	virtual void OnDraw(void) override;
	virtual void OnDestroy(void) override;
};