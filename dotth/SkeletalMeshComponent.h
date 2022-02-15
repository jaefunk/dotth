#pragma once

#include "MeshComponent.h"
#include "SkeletalMesh.h"
#include "Material.h"

class SkeletalMeshComponent : public MeshComponent
{
public:
	std::shared_ptr<Material> material{ new Material };
	std::shared_ptr<SkeletalMesh> mesh{ new SkeletalMesh };

public:
	virtual void OnInit(void) override;
	virtual void OnUpdate(void) override;
	virtual void OnDraw(void) override;
	virtual void OnDestroy(void) override;
};