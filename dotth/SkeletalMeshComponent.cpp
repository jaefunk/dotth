#include "SkeletalMeshComponent.h"
#include "Camera.h"


void SkeletalMeshComponent::OnInit(void)
{	
	
	mesh->Load("Resource/Breathing Idle.fbx");	
	animation->Load("Resource/Breathing Idle.fbx", mesh);

	material->Load("viking_blue_C_texture", "../Output/Client/x64/Debug/skin_vs.cso", "../Output/Client/x64/Debug/skin_ps.cso");

	//mesh->Load("Resource/OrangeBOT_FBX.fbx");
	//animation->Load("Resource/OrangeBOT_FBX", mesh);
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
		std::vector<XMMATRIX> calcBoneList;
		calcBoneList.resize(128);
		if (!mesh->Raw->meshes[i]->boneIds.empty())
		{
			for (int i = 0; i < 128; ++i)
			{
				calcBoneList[i] = XMMatrixTranspose(XMMATRIX(animation->finalMatrixes[i].f));
			}
		}
		material->Bind(world, view, proj, calcBoneList.data(), calcBoneList.size() * sizeof(XMMATRIX));
		mesh->Draw(i);
	}
}

void SkeletalMeshComponent::OnDestroy(void)
{
}

