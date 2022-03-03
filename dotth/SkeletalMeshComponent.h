#pragma once

#include "MeshComponent.h"
#include "SkeletalMesh.h"
#include "Material.h"
#include "AnimationController.h"

class SkeletalMeshComponent : public MeshComponent
{
public:
	std::shared_ptr<Material> material{ new Material };
	std::shared_ptr<Material> material2{ new Material };
	std::shared_ptr<SkeletalMesh> mesh{ new SkeletalMesh };
	std::shared_ptr<Animation> animation{ new Animation };

	std::shared_ptr<AnimationController> animationController{ new AnimationController };

	// origin animation update
	// [?] blend animation update
	// calc final animation
	// calc final bone matrix

public:
	virtual void OnInit(void) override;
	virtual void OnUpdate(void) override;
	virtual void OnDraw(void) override;
	virtual void OnDestroy(void) override;
};