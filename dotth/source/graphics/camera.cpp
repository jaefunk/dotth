
#include "camera.h"

DirectX::XMMATRIX * camera::get_view(void)
{
	return &_view;
}

DirectX::XMMATRIX * camera::get_pers(void)
{
	return &_pers;
}

DirectX::XMMATRIX * camera::get_ortho(void)
{
	return &_ortho;
}

void camera::set_eye(const DirectX::XMFLOAT3 & f3)
{
	_dirty[FLAG::VIEW] = true;
	_eye = f3;
}

void camera::set_up(const DirectX::XMFLOAT3 & f3)
{
	_dirty[FLAG::VIEW] = true;
	_up = f3;
}

void camera::set_at(const DirectX::XMFLOAT3 & f3)
{
	_dirty[FLAG::VIEW] = true;
	_at = f3;
}

void camera::set_fov(const float & f)
{
	_dirty[FLAG::PERSPECTIVE] = true;
	_fov = f;
}

void camera::set_aspect(const int & width, const int & height)
{
	_dirty[FLAG::PERSPECTIVE] = true;
	_dirty[FLAG::ORTHO] = true;
	_width = width;
	_height = height;
}

void camera::set_near(const float & f)
{
	_dirty[FLAG::PERSPECTIVE] = true;
	_dirty[FLAG::ORTHO] = true;
	_near = f;
}

void camera::set_far(const float & f)
{
	_dirty[FLAG::PERSPECTIVE] = true;
	_dirty[FLAG::ORTHO] = true;
	_far = f;
}

void camera::sync(void)
{
	if (_dirty[FLAG::VIEW] == true)
	{
		_dirty[FLAG::VIEW] = false;
		_view = DirectX::XMMatrixLookAtLH(DirectX::XMLoadFloat3(&_eye), DirectX::XMLoadFloat3(&_at), DirectX::XMLoadFloat3(&_up));
	}

	if (_dirty[FLAG::PERSPECTIVE] == true)
	{
		_dirty[FLAG::PERSPECTIVE] = false;
		_pers = DirectX::XMMatrixPerspectiveFovLH(_fov, static_cast<float>(_width) / static_cast<float>(_height), _near, _far);
	}

	if (_dirty[FLAG::ORTHO] == true)
	{
		_dirty[FLAG::ORTHO] = false;
		_ortho = DirectX::XMMatrixOrthographicLH(static_cast<float>(_width), static_cast<float>(_height), _near, _far);
	}
}
