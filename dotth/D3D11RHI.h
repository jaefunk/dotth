#pragma once

#include "dotth.h"
#include "SingleInstance.h"
#include "D3D11.h"

class D3D11RHI : public SingleInstance<D3D11RHI>
{
private:
	HWND _Hwnd;
	unsigned int _Width;
	unsigned int _Height;

private:
	ID3D11Device* _Device;
	ID3D11DeviceContext* _Context;
	IDXGISwapChain* _SwapChain;
	ID3D11RenderTargetView* _BackBufferRTV;
	ID3D11DepthStencilView* _DepthStencilView;	
	D3D_FEATURE_LEVEL _FeatureLevel;
public:
	static ID3D11Device* Device()
	{
		return D3D11RHI::Instance()->_Device;
	}
	static ID3D11DeviceContext* Context()
	{
		return D3D11RHI::Instance()->_Context;
	}
	static IDXGISwapChain* SwapChain()
	{
		return D3D11RHI::Instance()->_SwapChain;
	}
	static ID3D11RenderTargetView* BackBuffer()
	{
		return D3D11RHI::Instance()->_BackBufferRTV;
	}

public:
	bool Initialize(HWND hwnd, unsigned int width, unsigned int height);

public:
	void Draw(void);
};