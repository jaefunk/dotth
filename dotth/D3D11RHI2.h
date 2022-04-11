#pragma once

#include "dotth.h"
#include "D3D11.h"
#include "D3D11DeferredBuffer.h"
#include "D3D11OrthoRect.h"

class D3D11RHI2
{
public:
	D3D11RHI2(void);
	~D3D11RHI2(void);

	bool Initialize(void* handle, unsigned int width, unsigned int height);
	bool InitializeImGui(void* handle, ID3D11Device* device, ID3D11DeviceContext* context);

	void StandbyDeferred(void);
	void Draw(void);
	void BeginImGui(void);
	void EndImGui(void);
	void Present(void);

private:
	D3D11DefferedRenderSystem deferredRenderSystem;

private:
	vector2i viewportSize;

private:
	ID3D11Device* device;
	ID3D11DeviceContext* context;
	IDXGISwapChain* swapChain;
	ID3D11RenderTargetView* renderTargetView;
	ID3D11RasterizerState* rasterizerState;
	ID3D11SamplerState* samplerState;
	ID3D11DepthStencilView* depthStencilView;
	ID3D11DepthStencilState* depthStencilState;
};

