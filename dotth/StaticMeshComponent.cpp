#include "StaticMeshComponent.h"
#include "Camera.h"

void StaticMeshComponent::OnInit(void)
{	
	mesh->Load("Breathing Idle");
	material->Load("viking_blue_C_texture", "../Output/Client/x64/Debug/deferred_vs.cso", "../Output/Client/x64/Debug/deferred_ps.cso");
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

	for (unsigned int i = 0; i < mesh->GetSectionSize(); ++i)
	{
		material->Bind(world, view, proj, nullptr, 0);
		mesh->Draw(i);
	}
}

void StaticMeshComponent::OnDestroy(void)
{
}

