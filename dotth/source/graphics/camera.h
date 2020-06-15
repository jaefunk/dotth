
#pragma once

#include "utility/single_instance.h"
#include <DirectXMath.h>

class camera : public single_instance<camera>
{
private:
	enum FLAG {
		VIEW, PERSPECTIVE, ORTHO, MAX
	};
	bool _dirty[FLAG::MAX] = { false, };
	DirectX::XMFLOAT3 _eye, _up, _at;
	float _near, _far, _fov;
	int _width, _height;
	float _left, _top, _right, _bottom;
	DirectX::XMMATRIX _view, _pers, _ortho;

public:
	DirectX::XMMATRIX* get_view(void);
	DirectX::XMMATRIX* get_pers(void);
	DirectX::XMMATRIX* get_ortho(void);
	void set_eye(const DirectX::XMFLOAT3& f3);
	void set_up(const DirectX::XMFLOAT3& f3);
	void set_at(const DirectX::XMFLOAT3& f3);
	void set_fov(const float& f);
	void set_aspect(const int& width, const int& height);
	void set_near(const float& f);
	void set_far(const float& f);
	void sync(void);
};