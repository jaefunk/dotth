#include "SkeletalMeshComponent.h"
#include "Camera.h"


void SkeletalMeshComponent::OnInit(void)
{	
	mesh->Load("Resource/Breathing Idle.fbx");
	material->Load("viking_blue_C_texture", "../Output/Client/x64/Debug/skin_vs.cso", "../Output/Client/x64/Debug/skin_ps.cso");
	animation->Load("Resource/Breathing Idle.fbx", mesh);
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
		if (!mesh->Raw->meshes[i]->boneIds.empty())
		{
			for (auto matrix : animation->finalMatrixes)
			{
				calcBoneList.push_back(XMMATRIX(matrix.f));				
			}
		}
		//for (unsigned int j = 0; j < mesh->Raw->meshes.size(); ++j)
		//{
		//	auto bone = mesh->Raw->meshes[i]->bones[j];
		//	calcBoneList.push_back(XMMatrixTranspose(XMMATRIX(bone->offset.f) * XMMATRIX(bone->targetNode->world.f)));
		//	//calcBoneList.push_back(XMMatrixIdentity());
		//}
		material->Bind(world, view, proj, calcBoneList.data(), calcBoneList.size() * sizeof(XMMATRIX));
		mesh->Draw(i);
	}
}

void SkeletalMeshComponent::OnDestroy(void)
{
}

