
#include "EntryPoint.h"
#include "SkeletalMeshObject.h"
#include "StaticMeshComponent.h"
#include "Camera.h"
#include "Math/Easing.h"
#include "InputSystem.h"
#include "MovementComponent.h"
#include "LineRenderer.h"

void EntryPoint::OnInit(void)
{
	GetActiveCamera()->GetCameraComponent()->SetEye(vector3(0.f, 1000.f, -1000.f));
	GetActiveCamera()->GetCameraComponent()->SetUp(vector3::up());
	GetActiveCamera()->GetCameraComponent()->SetAt(vector3(0.f, 0.f, 0.f));

	//{	// Plane
	//	auto Plane = std::make_shared<Object>();
	//	SpawnObject(Plane);
	//	Plane->Scaling(dotth::vector3(20.f, 20.f, 20.f));
	//	Plane->RotatePitch(3.14f * 0.5f);
	//	auto SMC = Plane->AddComponent<StaticMeshComponent>();
	//	auto SM = new StaticMesh;
	//	SM->Load("Resource/Plane.fbx");
	//	SM->GetMaterial(0)->Load("uv_checker", "../Output/Client/x64/Debug/deferred_vs.cso", "../Output/Client/x64/Debug/deferred_ps.cso");
	//	SMC->SetStaticMesh(SM);
	//}

	{	// Human
		skeltalMeshObject = SpawnObject<SkeletalMeshObject>();
		
		if (std::shared_ptr<MovementComponent> movemoentComponent = skeltalMeshObject->AddComponent<MovementComponent>())
		{
			movemoentComponent->OnReached = std::bind(&EntryPoint::BindOnReached, this);
			movemoentComponent->OnMove = std::bind(&EntryPoint::BindOnMove, this, std::placeholders::_1, std::placeholders::_2);
		}

		// set skeletal mesh
		if (SkeletalMesh* skeletalMesh = new SkeletalMesh)
		{
			skeletalMesh->Load("Resource/Idle.fbx");
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
		}
	}
	
	InputSystem::BindInputDelegate(this, std::bind(&EntryPoint::BindTestFunction, this, std::placeholders::_1, std::placeholders::_2));
}

void EntryPoint::OnUpdate(void)
{
	auto p = skeltalMeshObject->GetLocalPosition();
	{
		Line line;
		line.from = dotth::vector3(0.f, 0.f, 0.f) + p;
		line.to = dotth::vector3(0.f, 500.f, 0.f) + p;
		line.color = dotth::vector4(0.f, 1.f, 0.f, 1.f);
		line.duration = 0.f;
		LineRenderer::Push(line);
	}
	{
		Line line;
		line.from = dotth::vector3(0.f, 0.f, 0.f) + p;
		line.to = dotth::vector3(500.f, 0.f, 0.f) + p;
		line.color = dotth::vector4(1.f, 0.f, 0.f, 1.f);
		line.duration = 0.f;
		LineRenderer::Push(line);
	}
	{
		Line line;
		line.from = dotth::vector3(0.f, 0.f, 0.f) + p;
		line.to = dotth::vector3(0.f, 0.f, 500.f) + p;
		line.color = dotth::vector4(0.f, 0.f, 1.f, 1.f);
		line.duration = 0.f;
		LineRenderer::Push(line);
	}
	
	for (auto x = 0; x < 21; ++x)
	{
		{
			Line line;
			line.from = dotth::vector3(-500 + 0.f, 0.f, -500 + x * 50.f);
			line.to = dotth::vector3(-500 + 1000.f, 0.f, -500 + x * 50.f);
			line.color = dotth::vector4(1.f, 1.f, 1.f, 1.f);
			line.duration = 0.f;
			LineRenderer::Push(line);
		}
		
		{
			Line line;
			line.from = dotth::vector3(-500 + x * 50.f, 0.f, -500);
			line.to = dotth::vector3(-500 + x * 50.f, 0.f, 1000.f - 500);
			line.color = dotth::vector4(1.f, 1.f, 1.f, 1.f);
			line.duration = 0.f;
			LineRenderer::Push(line);
		}
	}
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
	
	
	ImGui::Begin("EntryPoint");
	{
		static float eye[3] = { 0.f, 200.f, -500.f };
		if (ImGui::DragFloat3("eye", eye, 1.f, -1000.f, 1000.f, "%f"))
		{
			GetActiveCamera()->GetCameraComponent()->SetEye(dotth::vector3(eye));
		}

		static float at[3] = { 0.f, 0.f, 0.f };
		if (ImGui::DragFloat3("at", at, 1.f, -1000.f, 1000.f, "%f"))
		{
			GetActiveCamera()->GetCameraComponent()->SetAt(dotth::vector3(at));
		}

		static float fov = 90.f;
		if (ImGui::DragFloat("fov", &fov, 1.f, 0.f, 180.f, "%f"))
		{
			float jj = (fov / 180.f) * 3.141592f;
			GetActiveCamera()->GetCameraComponent()->SetFieldOfView(jj);
		}
	}
	ImGui::End();
}

void EntryPoint::BindTestFunction(InputState is, InputKey ik)
{
	if (ik == InputKey::Mouse_Right)
	{
		if (is == InputState::Press)
		{
			ViewInfo vi;
			GetActiveCamera()->GetCameraComponent()->GetViewInfo(vi);
			vector3 diff;
			dotth::vector3::subtract(vi.At, vi.Eye, diff);

			vector3 origin, direction;
			D3D11RHI::ScreenToWorld(vi, InputSystem::GetMousePosition(), origin, direction);

			vector3 start, end;
			start = origin;
			end = origin + (direction * 3000.f);
			
			vector3 result;
			float K = (0 - start.y) / (end.y - start.y);
			result.x = K * (end.x - start.x) + start.x;
			result.z = K * (end.z - start.z) + start.z;
			skeltalMeshObject->FindComponent<MovementComponent>()->MoveTo(result);
			animationController->BlendTo(1);
			//skeltalMeshObject->SetPosition(result);
		}
	}
}

void EntryPoint::BindOnReached(void)
{
	animationController->BlendTo(0);
}

void EntryPoint::BindOnMove(float remainTime, float remainDistance)
{
	if (remainTime <= 2.f)
		animationController->BlendTo(0);
	//printf("%f %f\n", remainTime, remainDistance);
}