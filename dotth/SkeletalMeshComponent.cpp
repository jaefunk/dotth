#include "SkeletalMeshComponent.h"
#include "Camera.h"


void SkeletalMeshComponent::OnInit(void)
{	
	
	mesh->Load("Resource/Breathing Idle.fbx");	
	animation->Load("Resource/Breathing Idle.fbx", mesh);

	material->Load("viking_blue_C_texture", "../Output/Client/x64/Debug/skin_vs.cso", "../Output/Client/x64/Debug/skin_ps.cso");
}

void SkeletalMeshComponent::OnUpdate(void)
{
	animation->Update(1.f);
}

void SkeletalMeshComponent::OnDraw(void)
{
	XMFLOAT4X4 world, view, proj;
	XMStoreFloat4x4(&world, GetOwner()->GetWorldMatrix());
	XMStoreFloat4x4(&view, XMMatrixTranspose(GetOwner()->GetActiveCamera()->GetView()));
	XMStoreFloat4x4(&proj, XMMatrixTranspose(GetOwner()->GetActiveCamera()->GetPerspective()));

	for (unsigned int i = 0; i < mesh->GetSectionSize(); ++i)
	{
		material->Bind(world, view, proj, animation->finalMatrixes.data(), animation->finalMatrixes.size() * sizeof(dotth2::matrix));
		mesh->Draw(i);
	}
}

void SkeletalMeshComponent::OnDestroy(void)
{
}

