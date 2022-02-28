#pragma once

#include "MeshComponent.h"
#include "SkeletalMesh.h"
#include "Material.h"
#include "Animation.h"

class SkeletalMeshComponent : public MeshComponent
{
public:
	std::shared_ptr<Material> material{ new Material };
	std::shared_ptr<Material> material2{ new Material };
	std::shared_ptr<SkeletalMesh> mesh{ new SkeletalMesh };
	std::shared_ptr<Animation> animation{ new Animation };

public:
	virtual void OnInit(void) override;
	virtual void OnUpdate(void) override;
	virtual void OnDraw(void) override;
	virtual void OnDestroy(void) override;
};