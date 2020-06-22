
#pragma once

#include "framework/component.h"
#include "graphics/renderer.h"

class model : public component
{
public:
	virtual void post_init(void) override
	{
		Initialize();
	}
	virtual void post_update(void) override
	{
	}
	virtual void post_render(void) override
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

