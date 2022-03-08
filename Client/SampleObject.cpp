#include "SampleObject.h"

void SampleObject::OnInit(void)
{
	skeletalMeshComponent = AddComponent<SkeletalMeshComponent>();
}

void SampleObject::OnDestroy(void)
{
}

void SampleObject::OnUpdate(void)
{	
}

void SampleObject::OnDraw(void)
{	
}

void SampleObject::OnDrawImGui(void)
{
	auto aa = &(skeletalMeshComponent->animationController->blendFactor);
	//ImGui::Begin("aa");
	ImGui::SliderFloat("aa", aa, 0.f, 1.f, "%f");
	//ImGui::End();
}