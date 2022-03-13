
#pragma once

#include "Object.h"

#include "SkeletalMeshComponent.h"
#include "AnimationController.h"

// animationController only status managing

class SkeletalMeshObject : public Object
{
public:
	SkeletalMeshObject(void);

private:
	std::shared_ptr<SkeletalMeshComponent> skeletalMeshComponent;
	AnimationController* animationController;

public:
	void SetSkeletalMesh(SkeletalMesh* inSkeletalMesh)
	{
		skeletalMeshComponent->SetSkeletalMesh(inSkeletalMesh);
	}
	void SetMaterial(int index, Material* inMaterial)
	{
	}

public:
	void SetAnimationController(AnimationController* inAnimationController)
	{
		animationController = inAnimationController;
	}

protected:
	virtual void OnInit(void) override;
	virtual void OnDestroy(void) override;
	virtual void OnUpdate(void) override;
	virtual void OnDraw(void) override;
	virtual void OnDrawImGui(void) override;
};