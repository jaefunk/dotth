
#include "CameraComponent.h"

CameraComponent::CameraComponent(void)
{
	FieldOfView = 90.f;
	AspectRatio = 1.77778f;
	OrthoWidth = 512.f;
	OrthoNearClipPlane = 0.f;
#ifdef max
#undef max
	OrthoFarClipPlane = std::numeric_limits<float>::max();	
#endif
}

void CameraComponent::OnInit(void)
{	
}

void CameraComponent::OnUpdate(void)
{
}

void CameraComponent::OnDraw(void)
{
}

void CameraComponent::OnDestroy(void)
{
}
