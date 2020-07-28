
#include "Camera.h"

DirectX::XMMATRIX * Camera::View(void)
{
	return &_View;
}

DirectX::XMMATRIX * Camera::Perspective(void)
{
	return &_Perspective;
}

DirectX::XMMATRIX * Camera::Ortho(void)
{
	return &_Ortho;
}

void Camera::SetEye(const DirectX::XMFLOAT3 & value)
{
	_DirtyFlags |= FLAG::VIEW;
	_Eye = value;
}

void Camera::SetUp(const DirectX::XMFLOAT3 & value)
{
	_DirtyFlags |= FLAG::VIEW;
	_Up = value;
}

void Camera::SetAt(const DirectX::XMFLOAT3 & value)
{
	_DirtyFlags |= FLAG::VIEW;
	_At = value;
}

void Camera::SetFieldOfView(const float & value)
{
	_DirtyFlags |= FLAG::PERSPECTIVE;
	_Fov = value;
}

void Camera::SetViewportSize(const int & width, const int & height)
{
	_DirtyFlags |= FLAG::PERSPECTIVE;
	_DirtyFlags |= FLAG::ORTHO;
	_Width = width;
	_Height = height;
}

void Camera::SetNear(const float & value)
{
	_DirtyFlags |= FLAG::PERSPECTIVE;
	_DirtyFlags |= FLAG::ORTHO;
	_Near = value;
}

void Camera::SetFar(const float & value)
{
	_DirtyFlags |= FLAG::PERSPECTIVE;
	_DirtyFlags |= FLAG::ORTHO;
	_Far = value;
}

void Camera::Sync(void)
{
	if (_DirtyFlags & FLAG::VIEW)
	{
		_View = DirectX::XMMatrixLookAtLH(DirectX::XMLoadFloat3(&_Eye), DirectX::XMLoadFloat3(&_At), DirectX::XMLoadFloat3(&_Up));
	}

	if (_DirtyFlags & FLAG::PERSPECTIVE)
	{
		_Perspective = DirectX::XMMatrixPerspectiveFovLH(_Fov, static_cast<float>(_Width) / static_cast<float>(_Height), _Near, _Far);
	}

	if (_DirtyFlags & FLAG::ORTHO)
	{
		_Ortho = DirectX::XMMatrixOrthographicLH(static_cast<float>(_Width), static_cast<float>(_Height), _Near, _Far);
	}
	_DirtyFlags = FLAG::NONE;
}
