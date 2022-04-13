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

	deferredRenderSystem.Initialize(device, context, width, height);

	InitializeImGui(handle, device, context);

	return true;
}

bool D3D11RHI2::InitializeImGui(void* handle, ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui::StyleColorsDark();
	ImGui_ImplWin32_Init(handle);
	ImGui_ImplDX11_Init(pDevice, pContext);
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
	deferredRenderSystem.Draw();
}

void D3D11RHI2::BeginImGui(void)
{
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
}

void D3D11RHI2::EndImGui(void)		
{
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

void D3D11RHI2::Present(void)
{
	swapChain->Present(1, 0);
}