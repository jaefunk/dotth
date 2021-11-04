
#include "CameraComponent.h"

CameraComponent::CameraComponent(int ViewportWidth, int ViewportHeight)
{
	Eye = Vector3(0.f, 500.f, -500.f);
	Up = Vector3::Up();
	At = Vector3::Zero();
	Near = 0.1f;
	Far = 100000.f;
	Fov = 3.141592f * 0.5f;
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

const Matrix& CameraComponent::GetView(void)
{
	return View;
}

const Matrix& CameraComponent::GetPerspective(void)
{
	return Perspective;
}

const Matrix& CameraComponent::GetOrtho(void)
{
	return Ortho;
}

void CameraComponent::SetEye(const Vector3& value)
{
	DirtyFlags |= CAMERA_TRANFSFORM_DIRTY_FLAG::VIEW;
	Eye = value;
}

void CameraComponent::SetUp(const Vector3& value)
{
	DirtyFlags |= CAMERA_TRANFSFORM_DIRTY_FLAG::VIEW;
	Up = value;
}

void CameraComponent::SetAt(const Vector3& value)
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
		XMFLOAT3 e = XMFLOAT3(Eye);
		XMFLOAT3 u = XMFLOAT3(Up);
		XMFLOAT3 a = XMFLOAT3(At);
		XMVECTOR EyeDirection = XMVectorSubtract(XMLoadFloat3(&a), XMLoadFloat3(&e));
		View = XMMatrixLookToLH(XMLoadFloat3(&e), EyeDirection, XMLoadFloat3(&u));
	}

	if (DirtyFlags & CAMERA_TRANFSFORM_DIRTY_FLAG::PERSPECTIVE)
	{
		Perspective = XMMatrixPerspectiveFovLH(Fov, static_cast<float>(Width) / static_cast<float>(Height), Near, Far);
	}

	if (DirtyFlags & CAMERA_TRANFSFORM_DIRTY_FLAG::ORTHO)
	{
		Ortho = XMMatrixOrthographicLH(static_cast<float>(Width), static_cast<float>(Height), 0.f, 1000.f);
	}
	DirtyFlags = CAMERA_TRANFSFORM_DIRTY_FLAG::NONE;
}
