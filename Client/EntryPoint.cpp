
#include "EntryPoint.h"
#include "SkeletalMeshObject.h"
#include "../dotth/StaticMeshComponent.h"
#include "Camera.h"
#include "../dotth/Math/Easing.h"

void EntryPoint::OnInit(void)
{
	GetActiveCamera()->GetCameraComponent()->SetEye(vector3(0.f, 1000.f, -500.f));
	GetActiveCamera()->GetCameraComponent()->SetUp(vector3::up());
	GetActiveCamera()->GetCameraComponent()->SetAt(vector3(0.f, 0.f, 0.f));

	// create
	auto skeltalMeshObject = std::make_shared<SkeletalMeshObject>();
	SpawnObject(skeltalMeshObject);

	// set skeletal mesh
	SkeletalMesh* skeletalMesh = new SkeletalMesh;
	skeletalMesh->Load("Resource/Human.fbx");
	skeltalMeshObject->SetSkeletalMesh(skeletalMesh);

	std::vector<std::string> boneNames;
	boneNames.resize(skeletalMesh->raw->mapBones.size());
	for (auto bones : skeletalMesh->raw->mapBones)
	{
		boneNames[bones.second.id] = bones.first;
	}

	// set animation control
	animationController = new AnimationController;
	animationController->Load("Resource/AnimControlHuman.json");
	animationController->model = skeletalMesh->raw;
	animationController->boneNames = boneNames;
	animationController->finalMatrixes.resize(animationController->boneNames.size());
	skeltalMeshObject->SetAnimationController(animationController);
	Animation* anim0 = new Animation();
	anim0->Load("Resource/Idle.fbx", skeletalMesh);
	animationController->SetAnimation(0, anim0);
	Animation* anim1 = new Animation();
	anim1->Load("Resource/Walk.fbx", skeletalMesh);
	animationController->SetAnimation(1, anim1);
	Animation* anim2 = new Animation();
	anim2->Load("Resource/Run.fbx", skeletalMesh);
	animationController->SetAnimation(2, anim2);
	Animation* anim3 = new Animation();
	anim3->Load("Resource/Jump.fbx", skeletalMesh);
	animationController->SetAnimation(3, anim3);

	animationController->BlendTo(0);


	auto Plane = std::make_shared<Object>();
	SpawnObject(Plane);
	Plane->Scaling(dotth::vector3(10.f, 10.f, 10.f));
	Plane->RotatePitch(3.14f * 0.5f);

	auto SMC = Plane->AddComponent<StaticMeshComponent>();

	auto SM = new StaticMesh;
	SM->Load("Resource/Plane.fbx");
	SM->GetMaterial(0)->Load("uv_checker", "../Output/Client/x64/Debug/deferred_vs.cso", "../Output/Client/x64/Debug/deferred_ps.cso");
	SMC->SetStaticMesh(SM);
}

void EntryPoint::OnUpdate(void)
{
}

//void EntryPoint::OnDraw(void)
//{
//}
//

void EntryPoint::OnDrawImGui(void)
{
	//float f = 0.f;
	std::string a[4];
	a[0] = "0";
	a[1] = "1";
	a[2] = "2";
	a[3] = "3";
	for (auto i = 0; i < 4; ++i) {
		if (ImGui::Button(a[i].c_str())) {
			animationController->BlendTo(i);
		}
	}
}
