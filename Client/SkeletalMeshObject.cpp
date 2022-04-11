
#include "SkeletalMeshObject.h"
#include "InputSystem.h"

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
	ImGui::Begin("SkeletalMeshObject");

	static std::string s[4] = {
		"idle", "walk", "run", "jump"
	};
	for (unsigned int a = 0; a < 4; ++a)
	{
		float weight = animationController->BlendSystem.Weight(a);
		ImGui::SliderFloat(s[a].c_str(), &weight, 0.f, 1.f, "%f");
	}
	ImGui::NewLine();
	ImGui::End();
}

void SkeletalMeshObject::BindTestFunction(InputState is, InputKey ik)
{
	if (InputKey::Mouse_Left == ik && InputState::Press == is) {
		auto mp = InputSystem::GetMousePosition();
		printf("%d left mouse button down on x = %d, y = %d\n", GetSerial(), mp.x, mp.y);
	}
}