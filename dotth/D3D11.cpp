
#include "D3D11.h"

static DXGI_SWAP_EFFECT GSwapEffect = DXGI_SWAP_EFFECT_DISCARD;
static DXGI_SCALING GSwapScaling = DXGI_SCALING_STRETCH;
static uint32_t GSwapChainBufferCount = 1;
static uint32_t GSwapChainFlags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

void D3D11::CreateDevice(ID3D11Device** ppDevice, ID3D11DeviceContext** ppDeviceContext)
{
	HRESULT result;

	D3D_FEATURE_LEVEL featureLevel = D3D_FEATURE_LEVEL_11_1;
	D3D_FEATURE_LEVEL outFeatureLevel;
	UINT createDeviceFlags = 0;
	result = D3D11CreateDevice(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		createDeviceFlags,
		&featureLevel,
		1,
		D3D11_SDK_VERSION,
		ppDevice,
		&outFeatureLevel,
		ppDeviceContext
	);
	assert(featureLevel == outFeatureLevel);
	assert(SUCCEEDED(result));
}

void D3D11::CreateSwapChain(void* handle, uint32_t width, uint32_t height, ID3D11Device* pDevice, IDXGISwapChain** ppSwapChain)
{
	HRESULT result;

	IDXGIFactory* factory = nullptr;
	result = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&factory);
	assert(SUCCEEDED(result));

	DXGI_SWAP_CHAIN_DESC swapChainDesc;
	memset(&swapChainDesc, 0, sizeof(DXGI_SWAP_CHAIN_DESC));
	swapChainDesc.OutputWindow = (HWND)handle;
	swapChainDesc.BufferCount = GSwapChainBufferCount;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT | DXGI_USAGE_SHADER_INPUT;
	swapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	swapChainDesc.Windowed = true;
	swapChainDesc.SwapEffect = GSwapEffect;
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;
	swapChainDesc.BufferDesc.Width = width;
	swapChainDesc.BufferDesc.Height = height;
	swapChainDesc.BufferDesc.RefreshRate.Numerator = 0;
	swapChainDesc.BufferDesc.RefreshRate.Denominator = 0;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	result = factory->CreateSwapChain(pDevice, &swapChainDesc, ppSwapChain);
	assert(SUCCEEDED(result));
}

void D3D11::CreateTexture2D(uint32_t width, uint32_t height, uint32_t mipLevels, uint32_t arraySize, DXGI_FORMAT format, uint32_t sampleCount, uint32_t sampleQuality, D3D11_USAGE usage, uint32_t bindFlags, uint32_t cpuAccessFlags, uint32_t miscFlags, ID3D11Device* pDevice, ID3D11Texture2D** ppTexture2D)
{
	HRESULT result;

	D3D11_TEXTURE2D_DESC desc;
	memset(&desc, 0, sizeof(D3D11_TEXTURE2D_DESC));
	desc.Width = width;
	desc.Height = height;
	desc.MipLevels = mipLevels;
	desc.ArraySize = arraySize;
	desc.Format = format;
	desc.SampleDesc.Count = sampleCount;
	desc.SampleDesc.Quality = sampleQuality;
	desc.Usage = usage;
	desc.BindFlags = bindFlags;
	desc.CPUAccessFlags = cpuAccessFlags;
	desc.MiscFlags = miscFlags;
	result = pDevice->CreateTexture2D(&desc, nullptr, ppTexture2D);
	assert(SUCCEEDED(result));
}

void D3D11::CreateDepthStencilState(ID3D11Device* pDevice, ID3D11DepthStencilState** ppDepthStencilState)
{
	HRESULT result;

	D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
	memset(&depthStencilDesc, 0, sizeof(D3D11_DEPTH_STENCIL_DESC));
	depthStencilDesc.DepthEnable = true;
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;
	depthStencilDesc.StencilEnable = true;
	depthStencilDesc.StencilReadMask = 0xFF;
	depthStencilDesc.StencilWriteMask = 0xFF;
	depthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	depthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
	depthStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
	depthStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
	result = pDevice->CreateDepthStencilState(&depthStencilDesc, ppDepthStencilState);
	assert(SUCCEEDED(result));
}

void D3D11::CreateDepthStencilView(ID3D11Device* pDevice, ID3D11Texture2D* pDepthStencilTexture, ID3D11DepthStencilView** ppDepthStencilView)
{
	HRESULT result;

	D3D11_DEPTH_STENCIL_VIEW_DESC desc;
	memset(&desc, 0, sizeof(D3D11_DEPTH_STENCIL_VIEW_DESC));
	desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	desc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	desc.Texture2D.MipSlice = 0;
	result = pDevice->CreateDepthStencilView(pDepthStencilTexture, &desc, ppDepthStencilView);
	assert(SUCCEEDED(result));
}

void D3D11::CreateRasterizerState(D3D11_FILL_MODE fillMode, D3D11_CULL_MODE cullMode, bool multiSampleEnable, ID3D11Device* pDevice, ID3D11RasterizerState** ppRasterrizerState)
{
	HRESULT result;

	D3D11_RASTERIZER_DESC desc;
	memset(&desc, 0, sizeof(D3D11_RASTERIZER_DESC));
	desc.CullMode = cullMode;
	desc.FillMode = fillMode;
	desc.MultisampleEnable = multiSampleEnable;
	desc.DepthBias = 0;
	desc.DepthBiasClamp = 0.f;
	desc.SlopeScaledDepthBias = 0.f;
	desc.FrontCounterClockwise = true;
	desc.DepthClipEnable = true;
	desc.ScissorEnable = true;
	result = pDevice->CreateRasterizerState(&desc, ppRasterrizerState);
	assert(SUCCEEDED(result));
}

void D3D11::CreateSamplerState(D3D11_TEXTURE_ADDRESS_MODE addressU, D3D11_TEXTURE_ADDRESS_MODE addressV, D3D11_TEXTURE_ADDRESS_MODE addressW, ID3D11Device* pDevice, ID3D11SamplerState** ppSamplerState)
{
	HRESULT result;

	D3D11_SAMPLER_DESC desc;
	memset(&desc, 0, sizeof(D3D11_SAMPLER_DESC));
	desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	desc.AddressU = addressU;
	desc.AddressV = addressV;
	desc.AddressW = addressW;
	desc.MipLODBias = 0.f;
	desc.MaxAnisotropy = 0;
	desc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	desc.MinLOD = 0.f;
	desc.MaxLOD = D3D11_FLOAT32_MAX;
	result = pDevice->CreateSamplerState(&desc, ppSamplerState);
	assert(SUCCEEDED(result));
}

void D3D11::CreateRenderTargetView(IDXGISwapChain* pSwapChain, ID3D11Device* pDevice, ID3D11RenderTargetView** ppRenderTargetView)
{
	HRESULT result;

	ID3D11Texture2D* renderTargetTexture = nullptr;
	result = pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&renderTargetTexture);
	assert(SUCCEEDED(result));

	result = pDevice->CreateRenderTargetView(renderTargetTexture, nullptr, ppRenderTargetView);
	assert(SUCCEEDED(result));

	renderTargetTexture->Release();
}
