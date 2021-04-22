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
	if (D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, createDeviceFlags, featureLevelArray, 2, D3D11_SDK_VERSION, &sd, &D3D11RHI::Instance()->_SwapChain, &D3D11RHI::Instance()->_Device, &featureLevel, &D3D11RHI::Instance()->_Context) != S_OK)
		return false;

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
	if (Device()->CreateTexture2D(&depth_buffer_desc, NULL, &depth_stencil_buffer))
		return false;

	D3D11_DEPTH_STENCIL_VIEW_DESC depth_stencil_view_desc;
	ZeroMemory(&depth_stencil_view_desc, sizeof(depth_stencil_view_desc));
	depth_stencil_view_desc.Format = depth_buffer_desc.Format;
	depth_stencil_view_desc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	depth_stencil_view_desc.Texture2D.MipSlice = 0;
	if (Device()->CreateDepthStencilView(depth_stencil_buffer, &depth_stencil_view_desc, &D3D11RHI::Instance()->_DepthStencilView))
		return false;
	depth_stencil_buffer->Release();

	

	ID3D11Texture2D* pBackBuffer;
	D3D11RHI::Instance()->_SwapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));
	D3D11RHI::Instance()->_Device->CreateRenderTargetView(pBackBuffer, NULL, &D3D11RHI::Instance()->_BackBufferRTV);
	pBackBuffer->Release();
	   
	return true;
}

void D3D11RHI::PreDraw(void)
{
	//static XMVECTORF32 ClearColor = { 0.0f, 0.2f, 0.4f, 1.0f };
	//Context()->ClearRenderTargetView(BackBuffer(), ClearColor);
	//Context()->ClearDepthStencilView(DepthBuffer(), D3D11_CLEAR_DEPTH, 1.0f, 0);

	XMFLOAT4 clear_color = XMFLOAT4(0.145f, 0.145f, 0.145f, 1.00f);
	const float clear_color_with_alpha[4] = { clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w };
	D3D11RHI::Context()->OMSetRenderTargets(1, &D3D11RHI::Instance()->_BackBufferRTV, NULL);
	D3D11RHI::Context()->ClearRenderTargetView(D3D11RHI::Instance()->_BackBufferRTV, clear_color_with_alpha);
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

ID3D11Buffer * D3D11RHI::CreateBuffer(const D3D11_BUFFER_DESC* desc, const D3D11_SUBRESOURCE_DATA* data)
{
	ID3D11Buffer* buffer = nullptr;
	Device()->CreateBuffer(desc, data, &buffer);
	return buffer;
}

ID3D11VertexShader * D3D11RHI::CreateVertexShader(ID3D10Blob * blob)
{
	ID3D11VertexShader* shader = nullptr;
	Device()->CreateVertexShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, &shader);
	return shader;
}

ID3D11PixelShader * D3D11RHI::CreatePixelShader(ID3D10Blob * blob)
{
	ID3D11PixelShader* shader = nullptr;
	Device()->CreatePixelShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, &shader);
	return shader;
}

ID3D11InputLayout * D3D11RHI::CreateInputLayout(ID3D10Blob * blob, D3D11_INPUT_ELEMENT_DESC * desc, unsigned int desc_size)
{
	ID3D11InputLayout* layout = nullptr;
	Device()->CreateInputLayout(desc, desc_size, blob->GetBufferPointer(), blob->GetBufferSize(), &layout);
	return layout;
}
