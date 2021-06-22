#pragma once

#include "D3D11.h"

class D3D11Camera
{	
private:
	enum FLAG {
		NONE = 0x0000,
		VIEW = 0x0001,
		PERSPECTIVE = 0x0010,
		ORTHO = 0x0100
	};
	int _DirtyFlags = FLAG::NONE;
	XMMATRIX _View;
	XMMATRIX _Perspective;
	XMMATRIX _Ortho;

	XMFLOAT3 _Eye = XMFLOAT3(0.f, 0.f, 0.f);
	XMFLOAT3 _Up = XMFLOAT3(0.f, 0.f, 0.f);
	XMFLOAT3 _At = XMFLOAT3(0.f, 0.f, 0.f);
	float _Near = 0.f;
	float _Far = 0.f;
	float _Fov = 0.f;
	int _Width = 0;
	int _Height = 0;

public:
	const XMMATRIX& View(void);
	const XMMATRIX& Perspective(void);
	const XMMATRIX& Ortho(void);
	void SetEye(const XMFLOAT3& value);
	void SetUp(const XMFLOAT3& value);
	void SetAt(const XMFLOAT3& value);
	void SetFieldOfView(const float& value);
	void SetViewportSize(const int& width, const int& height);
	void SetNear(const float& value);
	void SetFar(const float& value);

public:
	void Sync(void);
};

