#pragma once

#include <Windows.h>
#include <d3d11.h>
#pragma comment(lib, "d3d11.lib")

class D3D11RHI
{
private:
	HWND _Hwnd;
	unsigned int _Width;
	unsigned int _Height;
	ID3D11Device* _Device;
	ID3D11DeviceContext* _Context;
	IDXGISwapChain* _SwapChain;
	ID3D11RenderTargetView* _BackBufferRTV;
	ID3D11DepthStencilView* _DepthStencilView;	
	D3D_FEATURE_LEVEL _FeatureLevel;

public:
	bool Initialize(HWND hwnd, unsigned int width, unsigned int height);

public:
	void Draw(void);
	
};