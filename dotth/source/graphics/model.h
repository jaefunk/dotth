
#pragma once

#include "Framework/Component.h"
#include "Graphics/Renderer.h"

class model : public Component
{
public:
	virtual void OnInit(void) override
	{
		Initialize();
	}
	virtual void OnUpdate(void) override
	{
	}
	virtual void OnDraw(void) override
	{
		Render();
	}
private:
	struct VertexType
	{
		XMFLOAT3 position;
		XMFLOAT4 color;
	};

public:
	bool Initialize(void);
	void Shutdown();
	void Render(void);
	int GetIndexCount();

private:
	ID3D11Buffer* m_vertexBuffer = nullptr;
	ID3D11Buffer* m_indexBuffer = nullptr;
	int m_vertexCount = 0;
	int m_indexCount = 0;
};

