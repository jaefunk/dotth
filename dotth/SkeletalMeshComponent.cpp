#include "SkeletalMeshComponent.h"
#include "Camera.h"


void SkeletalMeshComponent::OnInit(void)
{	
	mesh->Load("viking_C");
	material->Load("viking_blue_C_texture", "../Output/Client/x64/Debug/skin_vs.cso", "../Output/Client/x64/Debug/skin_ps.cso");
	animation->Load(mesh->Raw);
}

void SkeletalMeshComponent::OnUpdate(void)
{
	animation->Update(0.1f);
}

void SkeletalMeshComponent::OnDraw(void)
{
	XMFLOAT4X4 world, view, proj;
	XMStoreFloat4x4(&world, GetOwner()->GetWorldMatrix());
	XMStoreFloat4x4(&view, XMMatrixTranspose(GetOwner()->GetActiveCamera()->GetView()));
	XMStoreFloat4x4(&proj, XMMatrixTranspose(GetOwner()->GetActiveCamera()->GetPerspective()));

	for (unsigned int i = 0; i < mesh->GetSectionSize(); ++i)
	{
		std::vector<XMMATRIX> calcBoneList;
		for (unsigned int j = 0; j < mesh->Raw->meshes[i]->numBones; ++j)
		{
			auto bone = mesh->Raw->meshes[i]->bones[j];
			calcBoneList.push_back(XMMatrixTranspose(XMMATRIX(bone->offset.f) * XMMATRIX(bone->targetNode->world.f)));
			//calcBoneList.push_back(XMMatrixIdentity());
		}
		material->Bind(world, view, proj, calcBoneList.data(), calcBoneList.size() * sizeof(XMMATRIX));
		mesh->Draw(i);
	}
}

void SkeletalMeshComponent::OnDestroy(void)
{
}

