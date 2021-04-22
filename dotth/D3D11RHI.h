#pragma once

#include "D3D11.h"
#include "dotth.h"
#include "SingleInstance.h"

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
	static bool Initialize(HWND hwnd, unsigned int width, unsigned int height);

public:
	static void PreDraw(void);
	static void PostDraw(void);

public:
	static ID3D11Device* Device();
	static ID3D11DeviceContext* Context();
	static IDXGISwapChain* SwapChain();
	static ID3D11RenderTargetView* BackBuffer();
	static ID3D11DepthStencilView* DepthBuffer();
	static ID3D11Buffer* CreateBuffer(const D3D11_BUFFER_DESC* desc, const D3D11_SUBRESOURCE_DATA* data);
	static ID3D11VertexShader* CreateVertexShader(ID3D10Blob* blob);
	static ID3D11PixelShader* CreatePixelShader(ID3D10Blob* blob);
	static ID3D11InputLayout* CreateInputLayout(ID3D10Blob* blob, D3D11_INPUT_ELEMENT_DESC* desc, unsigned int desc_size);
};