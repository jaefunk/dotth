#include "D3D11RHI2.h"

D3D11RHI2::D3D11RHI2(void)
{

}

D3D11RHI2::~D3D11RHI2(void)
{
}

bool D3D11RHI2::Initialize(void* handle, unsigned int width, unsigned int height)
{
	viewportSize = width;

	D3D11::CreateDevice(&device, &context);
	D3D11::CreateSwapChain(handle, width, height, device, &swapChain);

	ID3D11Texture2D* depthStencilTexture = nullptr;
	D3D11::CreateTexture2D(width, height, 1, 1, DXGI_FORMAT_D24_UNORM_S8_UINT, 1, 0, D3D11_USAGE_DEFAULT, D3D11_BIND_DEPTH_STENCIL, 0, 0, device, &depthStencilTexture);
	D3D11::CreateDepthStencilState(device, &depthStencilState);
	D3D11::CreateDepthStencilView(device, depthStencilTexture, &depthStencilView);
	depthStencilTexture->Release();

	D3D11::CreateRasterizerState(D3D11_FILL_SOLID, D3D11_CULL_BACK, true, device, &rasterizerState);
	D3D11::CreateRenderTargetView(swapChain, device, &renderTargetView);

	D3D11_VIEWPORT viewport;
	viewport.TopLeftX = 0.0f;
	viewport.TopLeftY = 0.0f;
	viewport.Width = static_cast<float>(width);
	viewport.Height = static_cast<float>(height);
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	context->RSSetViewports(1, &viewport);

	deferredRenderSystem.Initialize(device, width, height);

	//float left = (viewport.Width / 2.f) * -1.f;
	//float right = left + viewport.Width;
	//float top = viewport.Height * 0.5f;
	//float bottom = top - viewport.Height;

	//std::vector<dotth::vector3> positions = { {left, top, 0.f}, {right, top, 0.f}, {left, bottom, 0.f}, {right, bottom, 0.f} };
	//std::vector<dotth::vector2> textureCoords = { {0.f, 0.f}, {1.f, 0.f}, {0.f, 1.f}, {1.f, 1.f} };	
	//std::vector<unsigned int> indices = { 0, 1, 2, 1, 3, 2 };
	//renderTargetBuffer.AddVertexBuffer(device, positions.data(), sizeof(dotth::vector3), positions.size());
	//renderTargetBuffer.AddVertexBuffer(device, textureCoords.data(), sizeof(dotth::vector2), textureCoords.size());
	//renderTargetBuffer.SetIndexBuffer(device, indices.data(), sizeof(unsigned int), indices.size());

	InitializeImGui(handle, device, context);

	return true;
}

bool D3D11RHI2::InitializeImGui(void* handle, ID3D11Device* device, ID3D11DeviceContext* context)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui::StyleColorsDark();
	ImGui_ImplWin32_Init(handle);
	ImGui_ImplDX11_Init(device, context);
	return true;
}

void D3D11RHI2::StandbyDeferred(void)
{
	static float clearColor[4] = { 0.f, 0.f, 0.f, 0.f };
	deferredRenderSystem.CommitRenderTarget(context, depthStencilView);
	deferredRenderSystem.ClearRenderTarget(context, clearColor);
	context->ClearDepthStencilView(depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.f, 0);
}

void D3D11RHI2::Draw(void)
{
	static float clearColor[4] = { 0.f, 0.f, 0.f, 0.f };
	context->OMSetRenderTargets(1, &renderTargetView, depthStencilView);
	context->ClearRenderTargetView(renderTargetView, clearColor);
	context->OMSetDepthStencilState(depthStencilState, 0);

	//renderTargetBuffer.Draw(context);
}

void D3D11RHI2::BeginImGui(void)
{

}

void D3D11RHI2::EndImGui(void)
{

}

void D3D11RHI2::Present(void)
{

}