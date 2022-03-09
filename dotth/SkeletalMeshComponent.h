#pragma once

#include "MeshComponent.h"
#include "SkeletalMesh.h"
#include "Material.h"
#include "AnimationController.h"

class SkeletalMeshComponent : public MeshComponent
{
private:
	SkeletalMesh* skeletalMesh;
public:
	void SetSkeletalMesh(SkeletalMesh* inSkeletalMesh)
	{
		if (skeletalMesh != inSkeletalMesh)
			skeletalMesh = inSkeletalMesh;
	}

private:
	std::vector<Material*> materials;

public:
	std::vector<dotth::matrix> finalMatrixes;

public:
	virtual void OnInit(void) override;
	virtual void OnUpdate(void) override;
	virtual void OnDraw(void) override;
	virtual void OnDestroy(void) override;
};