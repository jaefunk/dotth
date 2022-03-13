
#include "EntryPoint.h"
#include "SkeletalMeshObject.h"
#include "Camera.h"

void EntryPoint::OnInit(void)
{
	GetActiveCamera()->GetCameraComponent()->SetEye(vector3(0.f, 100.f, -500.f));
	GetActiveCamera()->GetCameraComponent()->SetUp(vector3::up());
	GetActiveCamera()->GetCameraComponent()->SetAt(vector3(0.f, 100.f, 0.f));

	// create
	auto skeltalMeshObject = std::make_shared<SkeletalMeshObject>();
	SpawnObject(skeltalMeshObject);

	// set skeletal mesh
	SkeletalMesh* skeletalMesh = new SkeletalMesh;
	skeletalMesh->Load("Resource/Idle.fbx");
	skeltalMeshObject->SetSkeletalMesh(skeletalMesh);

	// set animation control
	AnimationController* animationController = new AnimationController;
	animationController->Load("Resource/AnimControlHuman");
	skeltalMeshObject->SetAnimationController(animationController);
	Animation* anim0 = new Animation();
	anim0->Load("Resource/Idle.fbx", skeletalMesh);
	animationController->SetAnimation("idle", anim0);
	Animation* anim1 = new Animation();
	anim1->Load("Resource/Walk.fbx", skeletalMesh);
	animationController->SetAnimation("walk", anim1);
	Animation* anim2 = new Animation();
	anim2->Load("Resource/Run.fbx", skeletalMesh);
	animationController->SetAnimation("run", anim2);
	Animation* anim3 = new Animation();
	anim3->Load("Resource/Jump.fbx", skeletalMesh);
	animationController->SetAnimation("jump", anim3);

	//animationController->BlendTo("walk");
	animationController->BlendTo("jump");
}

void EntryPoint::OnUpdate(void)
{
	//obj->RotateYaw(obj->GetDeltaSeconds());
	//static bool b = false;
	//static float f = 0.f;
	//if (f >= 1.f)
	//{
	//	if (b == false)
	//	{
	//		printf("asdf\n");
	//		animationController->SetClip("run");
	//	}
	//	b = true;
	//}
	
	//if (f <= 0.f)
	//	b = true;
	//if (b == true)
		//f += GetDeltaSeconds();
	//else 
	//	f -= GetDeltaSeconds();
	//f = clamp(0.f, 1.f, f);
	//printf("%f\n", f);
	//float f2 = f;
	//FindObject("linear")->SetScale(Vector3((f2 * 1500.f) - 750.f , 0.f, 500.f));
	//float in = (easing::sin::out(f2) * 1500.f) - 750.f;
	//FindObject("in")->SetPosition(Vector3(in, 0.f, 400.f));
	//float out = (easing::quad::out(f2) * 1500.f) - 750.f;
	//FindObject("out")->SetPosition(Vector3(out, 0.f, 300.f));
	//float in_out = (easing::cubic::out(f2) * 1500.f) - 750.f;
	//FindObject("in_out")->SetPosition(Vector3(in_out, 0.f, 200.f));
}

//void EntryPoint::OnDraw(void)
//{
//}
//
void EntryPoint::OnDrawImGui(void)
{
}
