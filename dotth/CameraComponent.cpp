
#include "CameraComponent.h"

CameraComponent::CameraComponent(unsigned int ViewportWidth, unsigned int ViewportHeight)
{
	Eye = vector3(0.f, 250, -500.f);
	Up = vector3::up();
	At = vector3::zero();
	Near = 0.1f;
	Far = 100000.f;
	Fov = 3.141592f * 0.3f;
	Width = ViewportWidth;
	Height = ViewportHeight;
	DirtyFlags = CAMERA_TRANFSFORM_DIRTY_FLAG::ALL;
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

const matrix& CameraComponent::GetView(void)
{
	return View;
}

const matrix& CameraComponent::GetPerspective(void)
{
	return Perspective;
}

const matrix& CameraComponent::GetOrtho(void)
{
	return Ortho;
}

void CameraComponent::SetEye(const vector3& value)
{
	DirtyFlags |= CAMERA_TRANFSFORM_DIRTY_FLAG::VIEW;
	Eye = value;
}

void CameraComponent::SetUp(const vector3& value)
{
	DirtyFlags |= CAMERA_TRANFSFORM_DIRTY_FLAG::VIEW;
	Up = value;
}

void CameraComponent::SetAt(const vector3& value)
{
	DirtyFlags |= CAMERA_TRANFSFORM_DIRTY_FLAG::VIEW;
	At = value;
}

void CameraComponent::SetFieldOfView(float value)
{
	DirtyFlags |= CAMERA_TRANFSFORM_DIRTY_FLAG::PERSPECTIVE;
	Fov = value;
}

void CameraComponent::SetViewportSize(int width, int height)
{
	DirtyFlags |= CAMERA_TRANFSFORM_DIRTY_FLAG::PERSPECTIVE;
	DirtyFlags |= CAMERA_TRANFSFORM_DIRTY_FLAG::ORTHO;
	Width = width;
	Height = height;
}

void CameraComponent::SetNear(float value)
{
	DirtyFlags |= CAMERA_TRANFSFORM_DIRTY_FLAG::PERSPECTIVE;
	DirtyFlags |= CAMERA_TRANFSFORM_DIRTY_FLAG::ORTHO;
	Near = value;
}

void CameraComponent::SetFar(float value)
{
	DirtyFlags |= CAMERA_TRANFSFORM_DIRTY_FLAG::PERSPECTIVE;
	DirtyFlags |= CAMERA_TRANFSFORM_DIRTY_FLAG::ORTHO;
	Far = value;
}

void CameraComponent::Sync(void)
{
	if (DirtyFlags & CAMERA_TRANFSFORM_DIRTY_FLAG::VIEW)
	{
		XMFLOAT3 eye = XMFLOAT3(Eye);
		XMFLOAT3 up = XMFLOAT3(Up);
		XMFLOAT3 at = XMFLOAT3(At);
		XMVECTOR EyeDirection = XMVectorSubtract(XMLoadFloat3(&at), XMLoadFloat3(&eye));
		View = XMMatrixTranspose(XMMatrixLookToLH(XMLoadFloat3(&eye), EyeDirection, XMLoadFloat3(&up)));
	}

	if (DirtyFlags & CAMERA_TRANFSFORM_DIRTY_FLAG::PERSPECTIVE)
	{
		Perspective = XMMatrixTranspose(XMMatrixPerspectiveFovLH(Fov, static_cast<float>(Width) / static_cast<float>(Height), Near, Far));
	}

	if (DirtyFlags & CAMERA_TRANFSFORM_DIRTY_FLAG::ORTHO)
	{
		Ortho = XMMatrixOrthographicLH(static_cast<float>(Width), static_cast<float>(Height), 0.f, 1000.f);
	}
	DirtyFlags = CAMERA_TRANFSFORM_DIRTY_FLAG::NONE;
}
