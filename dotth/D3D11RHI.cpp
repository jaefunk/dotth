#include "D3D11RHI.h"
#include "D3D11Shader.h"

D3D11RHI::~D3D11RHI()
{
	D3D11RHI::Instance()->_Device->Release();
	D3D11RHI::Instance()->_Context->Release();;
	D3D11RHI::Instance()->_SwapChain->Release();
	D3D11RHI::Instance()->_BackBufferRTV->Release();
	D3D11RHI::Instance()->_RasterizerStateSolid->Release();
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

	const unsigned int RenderTargetWidth = width;
	const unsigned int RenderTargetHeight = height;
	DXGI_SWAP_CHAIN_DESC scd;
	ZeroMemory(&scd, sizeof(scd));

	scd.BufferCount = 1;
	scd.BufferDesc.Width = RenderTargetWidth;
	scd.BufferDesc.Height = RenderTargetHeight;
	scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	scd.BufferDesc.RefreshRate.Numerator = 60;
	scd.BufferDesc.RefreshRate.Denominator = 1;
	scd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	scd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	scd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	scd.OutputWindow = (HWND)hwnd;
	scd.SampleDesc.Count = 1;
	scd.SampleDesc.Quality = 0;
	scd.Windowed = true;
	scd.Flags = 0;

	if (FAILED(factory->CreateSwapChain(D3D11RHI::Instance()->_Device, &scd, &D3D11RHI::Instance()->_SwapChain)))
	{
		return false;
	}

	ID3D11Texture2D* backbuffer = nullptr;
	D3D11RHI::SwapChain()->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&backbuffer));
	D3D11RHI::Device()->CreateRenderTargetView(backbuffer, NULL, &D3D11RHI::Instance()->_BackBufferRTV);
	backbuffer->Release();

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
	D3D11RHI::Device()->CreateTexture2D(&db, NULL, &depthstencilbuffer);

	D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
	ZeroMemory(&depthStencilDesc, sizeof(depthStencilDesc));
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
	D3D11RHI::Device()->CreateDepthStencilState(&depthStencilDesc, &D3D11RHI::Instance()->_DepthStencilState);
	depthStencilDesc.DepthEnable = false;
	D3D11RHI::Device()->CreateDepthStencilState(&depthStencilDesc, &D3D11RHI::Instance()->_DepthDisableStencilState);
	D3D11RHI::Context()->OMSetDepthStencilState(D3D11RHI::Instance()->_DepthStencilState, 1);

	D3D11_DEPTH_STENCIL_VIEW_DESC dsvd;
	ZeroMemory(&dsvd, sizeof(dsvd));
	dsvd.Format = db.Format;
	dsvd.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	dsvd.Texture2D.MipSlice = 0;
	D3D11RHI::Device()->CreateDepthStencilView(depthstencilbuffer, &dsvd, &D3D11RHI::Instance()->_DepthStencilView);
	depthstencilbuffer->Release();

	D3D11RHI::Context()->OMSetRenderTargets(1, &D3D11RHI::Instance()->_BackBufferRTV, D3D11RHI::DepthStencilView());

	D3D11_RASTERIZER_DESC rd;
	ZeroMemory(&rd, sizeof(D3D11_RASTERIZER_DESC));
	rd.AntialiasedLineEnable = false;
	rd.CullMode = D3D11_CULL_BACK;
	rd.DepthBias = 0;
	rd.DepthBiasClamp = 0.0f;
	rd.DepthClipEnable = true;
	rd.FillMode = D3D11_FILL_SOLID;
	rd.FrontCounterClockwise = false;
	rd.MultisampleEnable = false;
	rd.ScissorEnable = false;
	rd.SlopeScaledDepthBias = 0.0f;
	D3D11RHI::Device()->CreateRasterizerState(&rd, &D3D11RHI::Instance()->_RasterizerStateSolid);
	D3D11RHI::Context()->RSSetState(D3D11RHI::Instance()->_RasterizerStateSolid);

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

	D3D11_VIEWPORT viewport;
	viewport.TopLeftX = 0.0f;
	viewport.TopLeftY = 0.0f;
	viewport.Width = static_cast<float>(RenderTargetWidth);
	viewport.Height = static_cast<float>(RenderTargetHeight);
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	D3D11RHI::Context()->RSSetViewports(1, &viewport);

	D3D11RHI::Instance()->_DeferredBuffer = std::make_shared<D3D11DeferredBuffer>();
	D3D11RHI::Instance()->_DeferredBuffer->Initialize(D3D11RHI::Device(), RenderTargetWidth, RenderTargetHeight);

	D3D11RHI::Instance()->_OrthoRect = std::make_shared<D3D11OrthoRect>();
	D3D11RHI::Instance()->_OrthoRect->Initialize(D3D11RHI::Device(), RenderTargetWidth, RenderTargetHeight);


	D3D11RHI::Instance()->_Light = std::make_shared<D3D11Light>();
	D3D11RHI::Instance()->_Light->Initialize(D3D11RHI::Device(), hwnd);
	//D3D11RHI::Instance()->_DeferredLightVertexShader = std::make_shared<SimpleVertexShader>(D3D11RHI::Device(), D3D11RHI::Context());
	//D3D11RHI::Instance()->_DeferredLightVertexShader->LoadShaderFile(L"../Output/Client/x64/Debug/light_vs.cso");
	//D3D11RHI::Instance()->_DeferredLightPixelShader = std::make_shared<SimplePixelShader>(D3D11RHI::Device(), D3D11RHI::Context());
	//D3D11RHI::Instance()->_DeferredLightPixelShader->LoadShaderFile(L"../Output/Client/x64/Debug/light_ps.cso");

	return true;
}

void D3D11RHI::InitializeImGui(HWND hwnd, unsigned int width, unsigned int height)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	//ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplWin32_Init(hwnd);
	ImGui_ImplDX11_Init(D3D11RHI::Device(), D3D11RHI::Context());
}

void D3D11RHI::StandbyDeferred(void)
{
	float clear_color_with_alpha[4] = { 0.f, 0.f, 0.f, 0.f };
	D3D11RHI::DeferredBuffer()->SetRenderTargets(D3D11RHI::Context());
	D3D11RHI::DeferredBuffer()->ClearRenderTargets(D3D11RHI::Context(), clear_color_with_alpha);
}

void D3D11RHI::Draw(void)
{
	float clear_color_with_alpha[4] = { 0.f, 0.f, 0.f, 0.f };
	D3D11RHI::Context()->OMSetRenderTargets(1, &D3D11RHI::Instance()->_BackBufferRTV, D3D11RHI::DepthStencilView());
	D3D11RHI::Context()->ClearRenderTargetView(D3D11RHI::BackBuffer(), clear_color_with_alpha);
	D3D11RHI::Context()->ClearDepthStencilView(D3D11RHI::DepthStencilView(), D3D11_CLEAR_DEPTH, 1.0f, 0);

	D3D11RHI::Context()->RSSetState(D3D11RHI::Instance()->_RasterizerStateSolid);
	D3D11RHI::Context()->OMSetDepthStencilState(D3D11RHI::Instance()->_DepthStencilState, 0);

	D3D11RHI::Instance()->_OrthoRect->Render(D3D11RHI::Context());

	auto camera = D3D11RHI::Instance()->_Camera;
	D3D11RHI::Instance()->_Light->Render(
		D3D11RHI::Context(), 6,
		XMMatrixIdentity(),
		XMMatrixIdentity(),
		camera.Ortho(),
		D3D11RHI::DeferredBuffer()->GetShaderResourceView(0),
		D3D11RHI::DeferredBuffer()->GetShaderResourceView(1),
		XMFLOAT3(-1.f, -1.f, 1.f));
}

void D3D11RHI::BeginImGui(void)
{
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
}

void D3D11RHI::EndImGui(void)
{
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

void D3D11RHI::Present(void)
{
	D3D11RHI::SwapChain()->Present(1, 0);
}


ID3D11Device* D3D11RHI::Device()
{
	return D3D11RHI::Instance()->_Device;
}

ID3D11DeviceContext* D3D11RHI::Context()
{
	return D3D11RHI::Instance()->_Context;
}

IDXGISwapChain* D3D11RHI::SwapChain()
{
	return D3D11RHI::Instance()->_SwapChain;
}

ID3D11RenderTargetView* D3D11RHI::BackBuffer()
{
	return D3D11RHI::Instance()->_BackBufferRTV;
}

ID3D11DepthStencilView* D3D11RHI::DepthStencilView()
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

std::shared_ptr<D3D11DeferredBuffer> D3D11RHI::DeferredBuffer(void)
{
	return D3D11RHI::Instance()->_DeferredBuffer;
}