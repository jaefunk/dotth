#pragma once

#pragma once

#include "StaticMesh.h"
#include "D3D11RHI.h"


class D3D11OrthoRect
{
private:
	struct VertexType
	{
		XMFLOAT3 position;
		XMFLOAT2 texture;
	};

public:
	bool Initialize(ID3D11Device* device, int width, int height);
	void Shutdown();
	void Render(ID3D11DeviceContext* context);
	int GetIndexCount();


private:
	ID3D11Buffer* _VertexBuffer = nullptr;
	ID3D11Buffer* _IndexBuffer = nullptr;
	int _VertexCount = 0;
	int _IndexCount = 0;
};