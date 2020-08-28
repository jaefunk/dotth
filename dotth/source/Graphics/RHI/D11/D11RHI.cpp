#include "Graphics/RHI/D11/D11RHI.h"
//#include "Graphics/RHI/D11/D11Resource.h"
#include "Graphics/Camera.h"

bool D11RHI::Init(void* handle, int width, int height)
{ 
	D3D_FEATURE_LEVEL feature_levels[] =
	{
		D3D_FEATURE_LEVEL_11_1,
		//D3D_FEATURE_LEVEL_11_0,
	};
	
	if (FAILED(D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE::D3D_DRIVER_TYPE_HARDWARE, nullptr, 0, feature_levels, sizeof(feature_levels) / sizeof(D3D_FEATURE_LEVEL), D3D11_SDK_VERSION, &_Device, nullptr, &_Context)))
		return false;

	IDXGIFactory* factory = nullptr;
	if (FAILED(CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&factory)))
		return false;
	
	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.BufferCount = 1;
	sd.BufferDesc.Width = width;
	sd.BufferDesc.Height = height;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = (HWND)handle;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.Windowed = true;
	if (FAILED(factory->CreateSwapChain(_Device, &sd, &_SwapChain)))
		return false;
	
	ID3D11Texture2D* back_buffer_ptr = nullptr;
	if (FAILED(_SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&back_buffer_ptr))))
		return false;
	if (FAILED(_Device->CreateRenderTargetView(back_buffer_ptr, NULL, &_RenderTargetView)))
		return false;
	back_buffer_ptr->Release();

	D3D11_RASTERIZER_DESC raster_desc;
	ZeroMemory(&raster_desc, sizeof(D3D11_RASTERIZER_DESC));
	raster_desc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
	//raster_desc.FillMode = D3D11_FILL_MODE::D3D11_FILL_WIREFRAME;
	raster_desc.CullMode = D3D11_CULL_MODE::D3D11_CULL_BACK;
	raster_desc.FrontCounterClockwise = false;
	raster_desc.AntialiasedLineEnable = true;
	_Device->CreateRasterizerState(&raster_desc, &_RasterizerState);
	_Context->RSSetState(_RasterizerState);

	D3D11_SAMPLER_DESC sampler_desc;
	ZeroMemory(&sampler_desc, sizeof(sampler_desc));
	sampler_desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sampler_desc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sampler_desc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sampler_desc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sampler_desc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	sampler_desc.MinLOD = 0;
	sampler_desc.MaxLOD = D3D11_FLOAT32_MAX;
	_Device->CreateSamplerState(&sampler_desc, &_SamplerState);

	D3D11_TEXTURE2D_DESC depth_buffer_desc;
	ZeroMemory(&depth_buffer_desc, sizeof(depth_buffer_desc));
	depth_buffer_desc.Width = width;
	depth_buffer_desc.Height = height;
	depth_buffer_desc.MipLevels = 1;
	depth_buffer_desc.ArraySize = 1;
	depth_buffer_desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depth_buffer_desc.SampleDesc.Count = 1;
	depth_buffer_desc.SampleDesc.Quality = 0;
	depth_buffer_desc.Usage = D3D11_USAGE_DEFAULT;
	depth_buffer_desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depth_buffer_desc.CPUAccessFlags = 0;
	depth_buffer_desc.MiscFlags = 0;
	ID3D11Texture2D* depth_stencil_buffer = nullptr;
	if (FAILED(_Device->CreateTexture2D(&depth_buffer_desc, NULL, &depth_stencil_buffer)))
		return false;
	
	D3D11_DEPTH_STENCIL_VIEW_DESC depth_stencil_view_desc;
	ZeroMemory(&depth_stencil_view_desc, sizeof(depth_stencil_view_desc));
	depth_stencil_view_desc.Format = depth_buffer_desc.Format;
	depth_stencil_view_desc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	depth_stencil_view_desc.Texture2D.MipSlice = 0;
	if (FAILED(_Device->CreateDepthStencilView(depth_stencil_buffer, &depth_stencil_view_desc, &_DepthBuffer)))
		return false;
	depth_stencil_buffer->Release();

	_Context->OMSetRenderTargets(1, &_RenderTargetView, _DepthBuffer);
	
	D3D11_VIEWPORT viewport;
	viewport.Width = static_cast<float>(width);
	viewport.Height = static_cast<float>(height);
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	viewport.TopLeftX = 0.0f;
	viewport.TopLeftY = 0.0f;

	_Context->RSSetViewports(1, &viewport);

	Camera::Instance()->SetViewportSize(width, height);

	return true;
}

void D11RHI::PreDraw(void)
{
	_Context->ClearRenderTargetView(_RenderTargetView, DirectX::Colors::MidnightBlue);
	_Context->ClearDepthStencilView(_DepthBuffer, D3D11_CLEAR_DEPTH, 1.0f, 0);
}

void D11RHI::PostDraw(void)
{
	_SwapChain->Present(0, 0);
}

bool D11RHI::Release(void)
{
	_Device->Release();
	_Context->Release();
	_SwapChain->Release();
	_RenderTargetView->Release();
	_DepthBuffer->Release();
	_RasterizerState->Release();
	_SamplerState->Release();
	return false;
}