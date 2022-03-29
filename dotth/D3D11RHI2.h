#pragma once

#include "dotth.h"
#include "D3D11.h"

class D3D11RHI2 : public SingleInstance<D3D11RHI2>
{
	PREVENT_INSTANCING(D3D11RHI2)
public:
	virtual ~D3D11RHI2();

	bool Initialize(void* handle, unsigned int width, unsigned int height);
	bool InitializeImGui(void* handle, ID3D11Device* device, ID3D11DeviceContext* context);

	void StandbyDeferred(void);
	void Draw(void);
	void BeginImGui(void);
	void EndImGui(void);
	void Present(void);

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
	D3D_FEATURE_LEVEL featureLevel;
};

