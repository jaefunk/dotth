#pragma once

#include "D3D11.h"

class D3D11Camera
{	
public:
	D3D11Camera();
	~D3D11Camera();

	void SetPosition(float, float, float);
	void SetRotation(float, float, float);

	void Render();
	void GetViewMatrix(XMMATRIX&);

private:
	XMFLOAT3 m_position;
	XMFLOAT3 m_rotation;
	XMMATRIX m_viewMatrix;
};

