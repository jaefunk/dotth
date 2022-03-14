
#include "EntryPoint.h"
#include "SkeletalMeshObject.h"
#include "Camera.h"
#include "../dotth/Math/Easing.h"

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

	animationController->BlendTo(0);
	//animationController->BlendTo("walk");
	//animationController->BlendTo("jump");

	//Blends[0].id = "a";
	//Blends[1].id = "b";
	//Blends[2].id = "c";
	//Blends[3].id = "d";
	//Blends[4].id = "e";
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

	//Blends.Update(GetDeltaSeconds());
	//for (auto i = 0; i < 5; ++i) {
	//	if (validIndex == i) {
	//		Blends[i].value += GetDeltaSeconds();
	//	}
	//	else {
	//		Blends[i].factor -= GetDeltaSeconds();
	//	}
	//	Blends[i].factor = clamp(0.f, 1.f, Blends[i].factor);
	//}
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
	//	f += Blends[i].value;
	//	ImGui::SliderFloat(Blends[i].id.c_str(), &Blends[i].value, 0.f, 1.f, "%f");
	//	ImGui::SameLine();
	//	
	//	std::string label = Blends[i].id + "-";		
	//	if (ImGui::Button(label.c_str()))
	//	{
	//		Blends.SetActiveIndex(i);
	//	}
	//	ImGui::NewLine();
	//}

	//ImGui::Text("%f", f);
}
