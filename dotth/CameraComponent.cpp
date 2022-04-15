
#include "CameraComponent.h"

CameraComponent::CameraComponent(unsigned int ViewportWidth, unsigned int ViewportHeight)
{
	Eye = vector3(0.f, 1, -2.f);
	Up = vector3::up();
	At = vector3::zero();
	Near = 1.f;
	Far = 10000.f;
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

void CameraComponent::GetViewInfo(ViewInfo& viewInfo)
{
	viewInfo.View = View.transpose();
	viewInfo.Perspective = Projection.transpose();
	viewInfo.Eye = Eye;
	viewInfo.Up = Up;
	viewInfo.At = At;
	viewInfo.Near = Near;
	viewInfo.Far = Far;
	viewInfo.Fov = Fov;
	viewInfo.Width = Width;
	viewInfo.Height = Height;
}

const matrix& CameraComponent::GetView(void)
{
	return View;
}

const matrix& CameraComponent::GetProjection(void)
{
	return Projection;
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
	DirtyFlags |= CAMERA_TRANFSFORM_DIRTY_FLAG::PROJECTION;
	Fov = std::max<float>(value, 1.f);
}

void CameraComponent::SetViewportSize(int width, int height)
{
	DirtyFlags |= CAMERA_TRANFSFORM_DIRTY_FLAG::PROJECTION;
	Width = width;
	Height = height;
}

void CameraComponent::SetNear(float value)
{
	DirtyFlags |= CAMERA_TRANFSFORM_DIRTY_FLAG::PROJECTION;
	Near = value;
}

void CameraComponent::SetFar(float value)
{
	DirtyFlags |= CAMERA_TRANFSFORM_DIRTY_FLAG::PROJECTION;
	Far = value;
}

void CameraComponent::Sync(void)
{
	if (DirtyFlags & CAMERA_TRANFSFORM_DIRTY_FLAG::VIEW)
	{
		XMFLOAT3 eye = Eye;// XMFLOAT3(Eye);
		XMFLOAT3 up = Up;// XMFLOAT3(Up);
		XMFLOAT3 at = At;// XMFLOAT3(At);
		View = XMMatrixTranspose(XMMatrixLookAtLH(XMLoadFloat3(&eye), XMLoadFloat3(&at), XMLoadFloat3(&up)));
	}

	if (DirtyFlags & CAMERA_TRANFSFORM_DIRTY_FLAG::PROJECTION)
	{
		Projection = XMMatrixTranspose(XMMatrixPerspectiveFovLH(Fov, static_cast<float>(Width) / static_cast<float>(Height), Near, Far));
	}

	DirtyFlags = CAMERA_TRANFSFORM_DIRTY_FLAG::NONE;
}
