#include "SkeletalMeshComponent.h"
#include "Camera.h"


void SkeletalMeshComponent::OnInit(void)
{	
	//mesh->Load("Resource/aa/Walk.fbx");
	mesh->Load("Resource/aa/Idle.fbx");
	//animation->Load("Resource/aa/Idle.fbx", mesh);
	animation->Load("Resource/aa/Run.fbx", mesh);
	material->Load("viking_blue_C_texture", "../Output/Client/x64/Debug/skin_vs.cso", "../Output/Client/x64/Debug/skin_ps.cso");
}

void SkeletalMeshComponent::OnUpdate(void)
{
	animation->Update(0.5f);
}

void SkeletalMeshComponent::OnDraw(void)
{
	XMFLOAT4X4 world, view, proj;
	world = GetOwner()->GetWorldMatrix();
	view = GetOwner()->GetActiveCamera()->GetView();
	proj = GetOwner()->GetActiveCamera()->GetPerspective();

	for (unsigned int i = 0; i < mesh->GetSectionSize(); ++i)
	{
		material->Bind(world, view, proj, animation->finalMatrixes.data(), animation->finalMatrixes.size() * sizeof(dotth::matrix));
		mesh->Draw(i);
	}
}

void SkeletalMeshComponent::OnDestroy(void)
{
}

