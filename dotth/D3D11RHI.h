#pragma once

#include "dotth.h"
#include "SingleInstance.h"
#include "D3D11DeferredBuffer.h"
#include "D3D11OrthoRect.h"
#include "D3D11Light.h"

class D3D11RHI : public SingleInstance<D3D11RHI>
{
	PREVENT_INSTANCING(D3D11RHI)
public:
	virtual ~D3D11RHI();
private:
	HWND _Hwnd;
	unsigned int _Width;
	unsigned int _Height;

private:
	ID3D11Device* _Device;
	ID3D11DeviceContext* _Context;
	IDXGISwapChain* _SwapChain;
	ID3D11RenderTargetView* _BackBufferRTV;
	ID3D11RasterizerState* _RasterizerStateSolid;
	ID3D11SamplerState* _SamplerState;
	ID3D11DepthStencilView* _DepthStencilView;	
	ID3D11DepthStencilState* _DepthStencilState;
	D3D_FEATURE_LEVEL _FeatureLevel;
	XMMATRIX _OrthoMatrix;
		
public:
	static bool Initialize(HWND hwnd, unsigned int width, unsigned int height);
	static void InitializeImGui(HWND hwnd, unsigned int width, unsigned int height);

public:
	static void StandbyDeferred(void);
	static void Draw(void);
	static void BeginImGui(void);
	static void EndImGui(void);
	

	static void Present(void);

public:
	static ID3D11Device* Device();
	static ID3D11DeviceContext* Context();
	static IDXGISwapChain* SwapChain();
	static ID3D11RenderTargetView* BackBuffer();
	static ID3D11DepthStencilView* DepthStencilView();
	static ID3D11SamplerState* Sampler();
	static ID3D11DepthStencilState* DepthStencilState();
	//static ID3D11RasterizerState Raster
	//static ID3D11Buffer* CreateBuffer(const D3D11_BUFFER_DESC* desc, const D3D11_SUBRESOURCE_DATA* data);
	//static ID3D11VertexShader* CreateVertexShader(ID3DBlob* blob);
	//static ID3D11PixelShader* CreatePixelShader(ID3DBlob* blob);
	//static ID3D11InputLayout* CreateInputLayout(ID3DBlob* blob, D3D11_INPUT_ELEMENT_DESC* desc, unsigned int desc_size);
	//static void BindVertexBuffer(ID3D11Buffer* buffer, unsigned int size, unsigned int offset = 0);
	//static void BindIndexBuffer(ID3D11Buffer* buffer);

private:
	std::shared_ptr<D3D11DeferredBuffer> _DeferredBuffer;
	std::shared_ptr<D3D11OrthoRect> _OrthoRect;
	std::shared_ptr<D3D11Light> _Light;
public:
	static std::shared_ptr<D3D11DeferredBuffer> DeferredBuffer(void);

	static void GetViewportSize(unsigned int& width, unsigned int& height);
};

