
#include "D3D11Camera.h"

const XMMATRIX& D3D11Camera::View(void)
{
	return DirectX::XMMatrixTranspose(_View);
}

const XMMATRIX& D3D11Camera::Perspective(void)
{
	return DirectX::XMMatrixTranspose(_Perspective);
}

const XMMATRIX& D3D11Camera::Ortho(void)
{
	return _Ortho;
}

void D3D11Camera::SetEye(const XMFLOAT3 & value)
{
	_DirtyFlags |= FLAG::VIEW;
	_Eye = value;
}

void D3D11Camera::SetUp(const XMFLOAT3 & value)
{
	_DirtyFlags |= FLAG::VIEW;
	_Up = value;
}

void D3D11Camera::SetAt(const XMFLOAT3 & value)
{
	_DirtyFlags |= FLAG::VIEW;
	_At = value;
}

void D3D11Camera::SetFieldOfView(const float & value)
{
	_DirtyFlags |= FLAG::PERSPECTIVE;
	_Fov = value;
}

void D3D11Camera::SetViewportSize(const int & width, const int & height)
{
	_DirtyFlags |= FLAG::PERSPECTIVE;
	_DirtyFlags |= FLAG::ORTHO;
	_Width = width;
	_Height = height;
}

void D3D11Camera::SetNear(const float & value)
{
	_DirtyFlags |= FLAG::PERSPECTIVE;
	_DirtyFlags |= FLAG::ORTHO;
	_Near = value;
}

void D3D11Camera::SetFar(const float & value)
{
	_DirtyFlags |= FLAG::PERSPECTIVE;
	_DirtyFlags |= FLAG::ORTHO;
	_Far = value;
}

void D3D11Camera::Sync(void)
{
	if (_DirtyFlags & FLAG::VIEW)
	{
		_View = XMMatrixLookAtLH(XMLoadFloat3(&_Eye), XMLoadFloat3(&_At), XMLoadFloat3(&_Up));
	}

	if (_DirtyFlags & FLAG::PERSPECTIVE)
	{
		_Perspective = XMMatrixPerspectiveFovLH(_Fov, static_cast<float>(_Width) / static_cast<float>(_Height), _Near, _Far);
	}

	if (_DirtyFlags & FLAG::ORTHO)
	{
		_Ortho = XMMatrixOrthographicLH(static_cast<float>(_Width), static_cast<float>(_Height), _Near, _Far);
	}
	_DirtyFlags = FLAG::NONE;
}
