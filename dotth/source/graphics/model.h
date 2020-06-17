
#pragma once

#include "framework/object.h"
#include "graphics/renderer.h"

class model : public object
{
public:
	virtual void on_init(void) override
	{
		Initialize();
	}
	virtual void on_update(void) override
	{
	}
	virtual void on_render(void) override
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

