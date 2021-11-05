
#include "Camera.h"
#include "D3D11RHI.h"

Camera::Camera(unsigned int width, unsigned int height)
{
	Comp = AddComponent<CameraComponent>(width, height);
}

void Camera::OnInit(void)
{
}

void Camera::OnDestroy(void)
{
}

void Camera::OnUpdate(void)
{
}

void Camera::OnDraw(void)
{
}

std::shared_ptr<CameraComponent> Camera::GetCameraComponent(void)
{
	return Comp;
}

const Matrix& Camera::GetView(void)
{
	return Comp->GetView();
}

const Matrix& Camera::GetPerspective(void)
{
	return Comp->GetPerspective();
}

const Matrix& Camera::GetOrtho(void)
{
	return Comp->GetOrtho();
}