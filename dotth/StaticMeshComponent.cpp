#include "StaticMeshComponent.h"
#include "D3D11StaticMesh.h"
#include "Object.h"

void StaticMeshComponent::OnInit(void)
{	
	_StaticMesh = std::make_shared<D3D11StaticMesh>();
	_StaticMesh->Load("");
}

void StaticMeshComponent::OnUpdate(void)
{
	MeshComponent::OnUpdate();
}

void StaticMeshComponent::OnDraw(void)
{
	_StaticMesh->Matrix = GetOwner()->GetTransform().ToMatrix(true);
	_StaticMesh->Draw();
}

void StaticMeshComponent::OnDestroy(void)
{
}


