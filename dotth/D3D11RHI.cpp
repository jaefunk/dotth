#include "D3D11RHI.h"

D3D11RHI::~D3D11RHI()
{
	D3D11RHI::Instance()->_Device->Release();
	D3D11RHI::Instance()->_Context->Release();;
	D3D11RHI::Instance()->_SwapChain->Release();
	D3D11RHI::Instance()->_BackBufferRTV->Release();
	D3D11RHI::Instance()->_RasterizerState->Release();
	D3D11RHI::Instance()->_SamplerState->Release();
	D3D11RHI::Instance()->_DepthStencilView->Release();;
}

bool D3D11RHI::Initialize(HWND hwnd, unsigned int width, unsigned int height)
{
	D3D11RHI::Instance()->_Camera.SetViewportSize(width, height);
	D3D11RHI::Instance()->_FeatureLevel = D3D_FEATURE_LEVEL_11_1;
	UINT createDeviceFlags = 0;
#if defined(DEBUG) || defined(_DEBUG)
	//createDeviceFlags |= D3D11_DEBUG;
#endif
	if (FAILED(D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE::D3D_DRIVER_TYPE_HARDWARE, nullptr, createDeviceFlags, &D3D11RHI::Instance()->_FeatureLevel, 1, D3D11_SDK_VERSION, &D3D11RHI::Instance()->_Device, nullptr, &D3D11RHI::Instance()->_Context)))
	{
		return false;
	}

	IDXGIFactory* factory = nullptr;
	if (FAILED(CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&factory)))
	{
		return false;
	}


	const unsigned int RenderTargetWidth = 1920;
	const unsigned int RenderTargetHeight = 1080;
	DXGI_SWAP_CHAIN_DESC scd;
	ZeroMemory(&scd, sizeof(scd));


	scd.BufferCount = 1;
	scd.BufferDesc.Width = RenderTargetWidth;
	scd.BufferDesc.Height = RenderTargetHeight;
	scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	scd.BufferDesc.RefreshRate.Numerator = 60;
	scd.BufferDesc.RefreshRate.Denominator = 1;
	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	scd.OutputWindow = (HWND)hwnd;
	scd.SampleDesc.Count = 1;
	scd.SampleDesc.Quality = 0;
	scd.Windowed = true;
	if (FAILED(factory->CreateSwapChain(D3D11RHI::Instance()->_Device, &scd, &D3D11RHI::Instance()->_SwapChain)))
	{
		return false;
	}

	ID3D11Texture2D* backbuffer = nullptr;
	if (FAILED(D3D11RHI::SwapChain()->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&backbuffer))))
	{
		return false;
	}
	if (FAILED(D3D11RHI::Device()->CreateRenderTargetView(backbuffer, NULL, &D3D11RHI::Instance()->_BackBufferRTV)))
	{
		return false;
	}
	backbuffer->Release();

	D3D11_RASTERIZER_DESC rd;
	ZeroMemory(&rd, sizeof(D3D11_RASTERIZER_DESC));
	rd.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
	//rd.FillMode = D3D11_FILL_MODE::D3D11_FILL_WIREFRAME;
	rd.CullMode = D3D11_CULL_MODE::D3D11_CULL_BACK;
	rd.FrontCounterClockwise = false;
	rd.AntialiasedLineEnable = true;
	rd.MultisampleEnable = true;
	if (FAILED(D3D11RHI::Device()->CreateRasterizerState(&rd, &D3D11RHI::Instance()->_RasterizerState)))
	{
		return false;
	}
	D3D11RHI::Context()->RSSetState(D3D11RHI::Instance()->_RasterizerState);

	D3D11_SAMPLER_DESC sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sd.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sd.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sd.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sd.ComparisonFunc = D3D11_COMPARISON_NEVER;
	sd.MinLOD = 0;
	sd.MaxLOD = D3D11_FLOAT32_MAX;
	if (FAILED(D3D11RHI::Device()->CreateSamplerState(&sd, &D3D11RHI::Instance()->_SamplerState)))
	{
		return false;
	}

	D3D11_TEXTURE2D_DESC db;
	ZeroMemory(&db, sizeof(db));
	db.Width = RenderTargetWidth;
	db.Height = RenderTargetHeight;
	db.MipLevels = 1;
	db.ArraySize = 1;
	db.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	db.SampleDesc.Count = 1;
	db.SampleDesc.Quality = 0;
	db.Usage = D3D11_USAGE_DEFAULT;
	db.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	db.CPUAccessFlags = 0;
	db.MiscFlags = 0;
	ID3D11Texture2D* depthstencilbuffer = nullptr;
	if (FAILED(D3D11RHI::Device()->CreateTexture2D(&db, NULL, &depthstencilbuffer)))
	{
		return false;
	}

	D3D11_DEPTH_STENCIL_VIEW_DESC dsvd;
	ZeroMemory(&dsvd, sizeof(dsvd));
	dsvd.Format = db.Format;
	dsvd.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	dsvd.Texture2D.MipSlice = 0;
	if (FAILED(D3D11RHI::Device()->CreateDepthStencilView(depthstencilbuffer, &dsvd, &D3D11RHI::Instance()->_DepthStencilView)))
	{
		return false;
	}
	depthstencilbuffer->Release();
	D3D11RHI::Context()->OMSetRenderTargets(1, &D3D11RHI::Instance()->_BackBufferRTV, D3D11RHI::DepthBuffer());

	//D3D11RHI::Context()->OMSetRenderTargets(1, &D3D11RHI::Instance()->_BackBufferRTV, nullptr);

	D3D11_VIEWPORT viewport;
	viewport.TopLeftX = 0.0f;
	viewport.TopLeftY = 0.0f;	
	viewport.Width = static_cast<float>(RenderTargetWidth);
	viewport.Height = static_cast<float>(RenderTargetHeight);
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	D3D11RHI::Context()->RSSetViewports(1, &viewport);


	return true;
}

void D3D11RHI::PreDraw(void)
{
	const float clear_color_with_alpha[4] = { 0.145f, 0.145f, 0.145f, 1.00f };
	D3D11RHI::Context()->ClearRenderTargetView(D3D11RHI::BackBuffer(), clear_color_with_alpha);
	D3D11RHI::Context()->ClearDepthStencilView(D3D11RHI::DepthBuffer(), D3D11_CLEAR_DEPTH, 1.0f, 0);
}

void D3D11RHI::PostDraw(void)
{
	D3D11RHI::SwapChain()->Present(1, 0);	
}

ID3D11Device * D3D11RHI::Device()
{
	return D3D11RHI::Instance()->_Device;
}

ID3D11DeviceContext * D3D11RHI::Context()
{
	return D3D11RHI::Instance()->_Context;
}

IDXGISwapChain * D3D11RHI::SwapChain()
{
	return D3D11RHI::Instance()->_SwapChain;
}

ID3D11RenderTargetView * D3D11RHI::BackBuffer()
{
	return D3D11RHI::Instance()->_BackBufferRTV;
}

ID3D11DepthStencilView* D3D11RHI::DepthBuffer()
{
	return D3D11RHI::Instance()->_DepthStencilView;
}

D3D11Camera* D3D11RHI::Camera()
{
	return &D3D11RHI::Instance()->_Camera;
}

ID3D11SamplerState* D3D11RHI::Sampler()
{
	return D3D11RHI::Instance()->_SamplerState;
}

//
//ID3D11Buffer * D3D11RHI::CreateBuffer(const D3D11_BUFFER_DESC* desc, const D3D11_SUBRESOURCE_DATA* data)
//{
//	ID3D11Buffer* buffer = nullptr;
//	Device()->CreateBuffer(desc, data, &buffer);
//	return buffer;
//}
//
//ID3D11VertexShader * D3D11RHI::CreateVertexShader(ID3DBlob * blob)
//{
//	ID3D11VertexShader* shader = nullptr;
//	Device()->CreateVertexShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, &shader);
//	return shader;
//}
//
//ID3D11PixelShader * D3D11RHI::CreatePixelShader(ID3DBlob * blob)
//{
//	ID3D11PixelShader* shader = nullptr;
//	Device()->CreatePixelShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, &shader);
//	return shader;
//}
//
//ID3D11InputLayout * D3D11RHI::CreateInputLayout(ID3DBlob * blob, D3D11_INPUT_ELEMENT_DESC * desc, unsigned int desc_size)
//{
//	ID3D11InputLayout* layout = nullptr;
//	Device()->CreateInputLayout(desc, desc_size, blob->GetBufferPointer(), blob->GetBufferSize(), &layout);
//	return layout;
//}
//
//void D3D11RHI::BindVertexBuffer(ID3D11Buffer* buffer, unsigned int size, unsigned int offset)
//{
//	D3D11RHI::Context()->IASetVertexBuffers(0, 1, &buffer, &size, &offset);
//	
//}
//
//void D3D11RHI::BindIndexBuffer(ID3D11Buffer* buffer)
//{
//	D3D11RHI::Context()->IASetIndexBuffer(buffer, DXGI_FORMAT_R32_UINT, 0);
//}
