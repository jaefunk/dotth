
#pragma once

#include "framework/base.h"
#include "graphics/renderer.h"
#include "graphics/type_vertex.h"

class model
{
private:
	struct VertexType
	{
		XMFLOAT3 position;
		XMFLOAT4 color;
	};

public:
	bool Initialize(ID3D11Device*);
	void Shutdown();
	void Render(ID3D11DeviceContext*);

	int GetIndexCount();

private:
	bool InitializeBuffers(ID3D11Device*);
	void ShutdownBuffers();
	void RenderBuffers(ID3D11DeviceContext*);

private:
	ID3D11Buffer* m_vertexBuffer = nullptr;
	ID3D11Buffer* m_indexBuffer = nullptr;
	int m_vertexCount = 0;
	int m_indexCount = 0;
};

