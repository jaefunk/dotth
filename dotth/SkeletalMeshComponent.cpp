#include "SkeletalMeshComponent.h"
#include "Camera.h"


void SkeletalMeshComponent::OnInit(void)
{	
	//mesh->Load("Resource/aa/Walk.fbx");
	mesh->Load("Resource/Idle.fbx");
	//animation->Load("Resource/aa/Idle.fbx", mesh);
	animation->Load("Resource/Run.fbx", mesh);
	material->Load("tex0", "../Output/Client/x64/Debug/skin_vs.cso", "../Output/Client/x64/Debug/skin_ps.cso");
	material2->Load("tex1", "../Output/Client/x64/Debug/skin_vs.cso", "../Output/Client/x64/Debug/skin_ps.cso");

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
		if (i == 0)
			material->Bind(world, view, proj, animation->finalMatrixes.data(), static_cast<unsigned int>(animation->finalMatrixes.size() * sizeof(dotth::matrix)));
		if (i == 1)
			material2->Bind(world, view, proj, animation->finalMatrixes.data(), static_cast<unsigned int>(animation->finalMatrixes.size() * sizeof(dotth::matrix)));
		mesh->Draw(i);
	}
}

void SkeletalMeshComponent::OnDestroy(void)
{
}

