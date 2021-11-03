#pragma once

#include "dotth.h"

enum DEFERRED_RENDER_TARGET_TYPE {
	POSITION,
	DIFFUSE,
	NORMAL,
	DEFERRED_RENDER_TARGET_TYPE_MAX,
};

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