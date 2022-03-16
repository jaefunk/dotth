
#include "EntryPoint.h"
#include "SkeletalMeshObject.h"
#include "../dotth/StaticMeshComponent.h"
#include "Camera.h"
#include "../dotth/Math/Easing.h"
#include "../dotth/InputSystem.h"

void EntryPoint::OnInit(void)
{
	GetActiveCamera()->GetCameraComponent()->SetEye(vector3(0.f, 1000.f, -500.f));
	GetActiveCamera()->GetCameraComponent()->SetUp(vector3::up());
	GetActiveCamera()->GetCameraComponent()->SetAt(vector3(0.f, 0.f, 0.f));

	//// create
	skeltalMeshObject = std::make_shared<SkeletalMeshObject>();
	SpawnObject(skeltalMeshObject);

	// set skeletal mesh
	SkeletalMesh* skeletalMesh = new SkeletalMesh;
	skeletalMesh->Load("Resource/Human.fbx");
	skeltalMeshObject->SetSkeletalMesh(skeletalMesh);

	// set animation control
	animationController = new AnimationController;
	animationController->Load("Resource/AnimControlHuman.json");
	animationController->model = skeletalMesh->raw;
	animationController->boneNames = skeletalMesh->boneNames;
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

	//auto Plane = std::make_shared<Object>();
	//SpawnObject(Plane);
	//Plane->Scaling(dotth::vector3(10.f, 10.f, 10.f));
	//Plane->RotatePitch(3.14f * 0.5f);
	//auto SMC = Plane->AddComponent<StaticMeshComponent>();
	//auto SM = new StaticMesh;
	//SM->Load("Resource/Plane.fbx");
	//SM->GetMaterial(0)->Load("uv_checker", "../Output/Client/x64/Debug/deferred_vs.cso", "../Output/Client/x64/Debug/deferred_ps.cso");
	//SMC->SetStaticMesh(SM);

	InputSystem::BindInputDelegate(this, std::bind(&EntryPoint::BindTestFunction, this, std::placeholders::_1, std::placeholders::_2));
}

void EntryPoint::OnUpdate(void)
{
}

void EntryPoint::OnDrawImGui(void)
{
	for (auto i = 0; i < 4; ++i) {
		
		if (ImGui::Button(std::to_string(i).c_str())) {
			animationController->BlendTo(i);
		}
	}

	if (ImGui::Button("asdf")) {
		if (skeltalMeshObject)
		{
			RemoveObject(skeltalMeshObject);
			skeltalMeshObject.reset();
		}
	}
}

void EntryPoint::BindTestFunction(InputState is, InputKey ik)
{
	if (ik == InputKey::Mouse_Right)
	{
		if (is == InputState::Press)
		{
			auto mp = InputSystem::GetMousePosition();
			printf("right mouse button down on x = %d, y = %d\n", mp.x, mp.y);
		}
	}
}