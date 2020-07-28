
#pragma once

#include "utility/SingleInstance.h"
#include <DirectXMath.h>

class Camera : public SingleInstance<Camera>
{
private:
	enum FLAG {
		NONE = 0x0000,
		VIEW = 0x0001, 
		PERSPECTIVE = 0x0010,
		ORTHO = 0x0100
	};
	int _DirtyFlags = FLAG::NONE;
	DirectX::XMMATRIX _View;
	DirectX::XMMATRIX _Perspective;
	DirectX::XMMATRIX _Ortho;

	DirectX::XMFLOAT3 _Eye = DirectX::XMFLOAT3(0.f, 0.f, 0.f);
	DirectX::XMFLOAT3 _Up = DirectX::XMFLOAT3(0.f, 0.f, 0.f);
	DirectX::XMFLOAT3 _At = DirectX::XMFLOAT3(0.f, 0.f, 0.f);
	float _Near = 0.f;
	float _Far = 0.f;
	float _Fov = 0.f;
	int _Width = 0;
	int _Height = 0;

public:
	DirectX::XMMATRIX* View(void);
	DirectX::XMMATRIX* Perspective(void);
	DirectX::XMMATRIX* Ortho(void);
	void SetEye(const DirectX::XMFLOAT3& value);
	void SetUp(const DirectX::XMFLOAT3& value);
	void SetAt(const DirectX::XMFLOAT3& value);
	void SetFieldOfView(const float& value);
	void SetViewportSize(const int& width, const int& height);
	void SetNear(const float& value);
	void SetFar(const float& value);

public:
	void Sync(void);
};