#pragma once

#include "D3D11.h"

class D3D11DeferredBuffer
{
public:
	D3D11DeferredBuffer();
	~D3D11DeferredBuffer();
	bool Initialize(ID3D11Device* device, unsigned int width, unsigned int height);
	void Destroy(void);
	void SetRenderTargets(ID3D11DeviceContext* context);
	void ClearRenderTargets(ID3D11DeviceContext* context, float* color);
	ID3D11ShaderResourceView* GetShaderResourceView(int index);

private:
	ID3D11Texture2D* RenderTargetTextureArray[DEFERRED_RENDER_TARGET_TYPE_MAX];
	ID3D11RenderTargetView* RenderTargetViewArray[DEFERRED_RENDER_TARGET_TYPE_MAX];
	ID3D11ShaderResourceView* ShaderResourceViewArray[DEFERRED_RENDER_TARGET_TYPE_MAX];
	ID3D11Texture2D* DepthStencilBuffer = nullptr;
	ID3D11DepthStencilView* DepthStencilView = nullptr;
	D3D11_VIEWPORT Viewport;
};


class OrthoWindowClass
{
public:
	struct VertexType
	{
		XMFLOAT3 position;
		XMFLOAT2 texture;
	};

	bool Initialize(ID3D11Device*, int, int);
	void Shutdown();
	void Render(ID3D11DeviceContext*);

	int GetIndexCount();

private:
	bool InitializeBuffers(ID3D11Device*, int, int);
	void ShutdownBuffers();
	void RenderBuffers(ID3D11DeviceContext*);

private:
	ID3D11Buffer* m_vertexBuffer = nullptr;
	ID3D11Buffer* m_indexBuffer = nullptr;
	int m_vertexCount = 0;
	int m_indexCount = 0;
};
