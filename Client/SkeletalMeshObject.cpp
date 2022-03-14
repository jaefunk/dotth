
#include "SkeletalMeshObject.h"

SkeletalMeshObject::SkeletalMeshObject(void)
{
	skeletalMeshComponent = AddComponent<SkeletalMeshComponent>();
}

void SkeletalMeshObject::OnInit(void)
{
}

void SkeletalMeshObject::OnDestroy(void)
{
}

void SkeletalMeshObject::OnUpdate(void)
{
	animationController->Update(GetDeltaSeconds());
	skeletalMeshComponent->finalMatrixes = animationController->finalMatrixes;
}

void SkeletalMeshObject::OnDraw(void)
{	
}

void SkeletalMeshObject::OnDrawImGui(void)
{
}