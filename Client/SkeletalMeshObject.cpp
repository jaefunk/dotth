
#include "SkeletalMeshObject.h"

SkeletalMeshObject::SkeletalMeshObject(void)
{
	skeletalMeshComponent = AddComponent<SkeletalMeshComponent>();

	InputSystem::BindInputDelegate(this, std::bind(&SkeletalMeshObject::BindTestFunction, this, std::placeholders::_1, std::placeholders::_2));
}

void SkeletalMeshObject::OnInit(void)
{
}

void SkeletalMeshObject::OnDestroy(void)
{
}

void SkeletalMeshObject::OnUpdate(void)
{
	animationController->Update(GetDeltaSeconds());
	skeletalMeshComponent->finalMatrixes = animationController->finalMatrixes;
}

void SkeletalMeshObject::OnDraw(void)
{	
}

void SkeletalMeshObject::OnDrawImGui(void)
{
}



void SkeletalMeshObject::BindTestFunction(InputState is, InputKey ik)
{
	if (InputKey::Mouse_Left == ik && InputState::Press == is) {
		auto mp = InputSystem::GetMousePosition();
		printf("%d left mouse button down on x = %d, y = %d\n", GetSerial(), mp.x, mp.y);
	}
}