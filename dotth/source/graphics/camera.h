
#pragma once

#include <DirectXMath.h>
using namespace DirectX;

class camera
{
public:
	void SetPosition(float, float, float);
	void SetRotation(float, float, float);

	XMFLOAT3 GetPosition();
	XMFLOAT3 GetRotation();

	void Render();
	void GetViewMatrix(XMMATRIX&);

private:
	XMFLOAT3 m_position = XMFLOAT3(0.f, 0.f, 0.f);
	XMFLOAT3 m_rotation = XMFLOAT3(0.f, 0.f, 0.f);;
	XMMATRIX m_viewMatrix;
};