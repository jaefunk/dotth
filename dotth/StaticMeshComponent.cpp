#include "StaticMeshComponent.h"
#include "Camera.h"

void StaticMeshComponent::OnInit(void)
{	
	
}

bool StaticMeshComponent::SetStaticMesh(std::shared_ptr<StaticMesh> NewMesh)
{
	if (NewMesh == staticMesh)
	{
		return false;
	}

	staticMesh = NewMesh;
	return true;
}

void StaticMeshComponent::Load1(void)
{
	staticMesh->Load("Sphere");
	material->Load("uv_checker", "../Output/Client/x64/Debug/deferred_vs.cso", "../Output/Client/x64/Debug/deferred_ps.cso");
}

void StaticMeshComponent::Load2(void)
{
	staticMesh->Load("Plane");
	material->Load("uv_checker", "../Output/Client/x64/Debug/deferred_vs.cso", "../Output/Client/x64/Debug/deferred_ps.cso");
}

void StaticMeshComponent::Load3(void)
{
	staticMesh->Load("Plane");
	material->Load("uv_checker", "../Output/Client/x64/Debug/deferred_vs.cso", "../Output/Client/x64/Debug/deferred_ps.cso");
}

void StaticMeshComponent::OnUpdate(void)
{
}

void StaticMeshComponent::OnDraw(void)
{
	XMFLOAT4X4 world, view, proj;
	XMStoreFloat4x4(&world, GetOwner()->GetWorldMatrix());
	XMStoreFloat4x4(&view, XMMatrixTranspose(GetOwner()->GetActiveCamera()->GetView()));
	XMStoreFloat4x4(&proj, XMMatrixTranspose(GetOwner()->GetActiveCamera()->GetPerspective()));

	for (unsigned int i = 0; i < staticMesh->GetSectionSize(); ++i)
	{
		material->Bind(world, view, proj);
		staticMesh->Draw(i);		
	}
}

void StaticMeshComponent::OnDestroy(void)
{
}


