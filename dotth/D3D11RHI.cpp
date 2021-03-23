#include "D3D11RHI.h"


bool D3D11RHI::Initialize(HWND hwnd, unsigned int width, unsigned int height)
{
	// Setup swap chain
	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.BufferCount = 2;
	sd.BufferDesc.Width = 0;
	sd.BufferDesc.Height = 0;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = hwnd;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.Windowed = TRUE;
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	UINT createDeviceFlags = 0;
	//createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
	D3D_FEATURE_LEVEL featureLevel;
	const D3D_FEATURE_LEVEL featureLevelArray[2] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_0, };
	if (D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, createDeviceFlags, featureLevelArray, 2, D3D11_SDK_VERSION, &sd, &_SwapChain, &_Device, &featureLevel, &_Context) != S_OK)
		return false;

	ID3D11Texture2D* pBackBuffer;
	_SwapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));
	_Device->CreateRenderTargetView(pBackBuffer, NULL, &_BackBufferRTV);
	pBackBuffer->Release();
	   
	return true;
}

void D3D11RHI::Draw(void)
{
	XMFLOAT4 clear_color = XMFLOAT4(0.145f, 0.145f, 0.145f, 1.00f);
	const float clear_color_with_alpha[4] = { clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w };
	_Context->OMSetRenderTargets(1, &_BackBufferRTV, NULL);
	_Context->ClearRenderTargetView(_BackBufferRTV, clear_color_with_alpha);
	_SwapChain->Present(1, 0);
}