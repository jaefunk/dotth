#include "SkeletalMeshComponent.h"
#include "Camera.h"


void SkeletalMeshComponent::OnInit(void)
{	
	//mesh->Load("Resource/aa/Walk.fbx");
	mesh->Load("Resource/Idle.fbx");
	animation->Load("Resource/Idle.fbx", mesh);

	Animation* anim0 = new Animation();
	anim0->Load("Resource/Idle.fbx", mesh);
	animationController->AddClip("idle", anim0);
	
	Animation* anim1 = new Animation();
	anim1->Load("Resource/Walk.fbx", mesh);
	animationController->AddClip("walk", anim1);

	Animation* anim2 = new Animation();
	anim2->Load("Resource/Run.fbx", mesh);
	animationController->AddClip("run", anim2);

	animationController->SetClip("walk");
	animationController->SetClip("run");
	

	material->Load("tex0", "../Output/Client/x64/Debug/skin_vs.cso", "../Output/Client/x64/Debug/skin_ps.cso");
	material2->Load("tex1", "../Output/Client/x64/Debug/skin_vs.cso", "../Output/Client/x64/Debug/skin_ps.cso");

}

void SkeletalMeshComponent::OnUpdate(void)
{
	float deltaSeconds = GetOwner()->GetDeltaSeconds();

	animationController->Update(0.016f);

	//static float f = 0.f;
	//static bool b = false;
	//f += deltaSeconds;
	//if (f >= 3.f)
	//{
	//	f = 0.f;
	//	b = !b;
	//	if (b)
	//		animationController->SetClip("run", 0.1f);
	//	else
	//		animationController->SetClip("walk", 0.1f);
	//}
	//animation->Update(0.5f);
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
			material->Bind(world, view, proj, animationController->finalMatrixes.data(), static_cast<unsigned int>(animationController->finalMatrixes.size() * sizeof(dotth::matrix)));
		if (i == 1)
			material2->Bind(world, view, proj, animationController->finalMatrixes.data(), static_cast<unsigned int>(animationController->finalMatrixes.size() * sizeof(dotth::matrix)));
		mesh->Draw(i);
	}
}

void SkeletalMeshComponent::OnDestroy(void)
{
}

