#pragma once

#include "D3D11.h"

class D3D11OrthoRect
{
public:
	struct VertexType
	{
		XMFLOAT3 position;
		XMFLOAT2 texture;
	};

	bool Initialize(ID3D11Device*, int, int);
	void Shutdown();
	void Render(ID3D11DeviceContext* context);
	int GetIndexCount();

private:
	ID3D11Buffer* _VertexBuffer = nullptr;
	ID3D11Buffer* _IndexBuffer = nullptr;
	int _VertexCount = 0;
	int _IndexCount = 0;
};
