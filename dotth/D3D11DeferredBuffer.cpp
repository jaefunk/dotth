#include "D3D11DeferredBuffer.h"
#include "D3D11RHI.h"

D3D11DeferredBuffer::D3D11DeferredBuffer()
{
}

D3D11DeferredBuffer::~D3D11DeferredBuffer()
{
}

bool D3D11DeferredBuffer::Initialize(ID3D11Device* device, unsigned int width, unsigned int height)
{
	D3D11_TEXTURE2D_DESC textureDesc;
	ZeroMemory(&textureDesc, sizeof(textureDesc));
	textureDesc.Width = width;
	textureDesc.Height = height;
	textureDesc.MipLevels = 1;
	textureDesc.ArraySize = 1;
	textureDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	textureDesc.SampleDesc.Count = 1;
	textureDesc.Usage = D3D11_USAGE_DEFAULT;
	textureDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	textureDesc.CPUAccessFlags = 0;
	textureDesc.MiscFlags = 0;

	D3D11_RENDER_TARGET_VIEW_DESC renderTargetViewDesc;
	renderTargetViewDesc.Format = textureDesc.Format;
	renderTargetViewDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
	renderTargetViewDesc.Texture2D.MipSlice = 0;

	D3D11_SHADER_RESOURCE_VIEW_DESC shaderResourceViewDesc;
	shaderResourceViewDesc.Format = textureDesc.Format;
	shaderResourceViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	shaderResourceViewDesc.Texture2D.MostDetailedMip = 0;
	shaderResourceViewDesc.Texture2D.MipLevels = 1;

	for (int index = 0; index < DEFERRED_RENDER_TARGET_TYPE_MAX; index++)
	{
		device->CreateTexture2D(&textureDesc, NULL, &RenderTargetTextureArray[index]);
		device->CreateRenderTargetView(RenderTargetTextureArray[index], &renderTargetViewDesc, &RenderTargetViewArray[index]);
		device->CreateShaderResourceView(RenderTargetTextureArray[index], &shaderResourceViewDesc, &ShaderResourceViewArray[index]);
	}

	D3D11_TEXTURE2D_DESC depthBufferDesc;
	ZeroMemory(&depthBufferDesc, sizeof(depthBufferDesc));
	depthBufferDesc.Width = width;
	depthBufferDesc.Height = height;
	depthBufferDesc.MipLevels = 1;
	depthBufferDesc.ArraySize = 1;
	depthBufferDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthBufferDesc.SampleDesc.Count = 1;
	depthBufferDesc.SampleDesc.Quality = 0;
	depthBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	depthBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthBufferDesc.CPUAccessFlags = 0;
	depthBufferDesc.MiscFlags = 0;
	device->CreateTexture2D(&depthBufferDesc, NULL, &DepthStencilBuffer);

	D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;
	ZeroMemory(&depthStencilViewDesc, sizeof(depthStencilViewDesc));
	depthStencilViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	depthStencilViewDesc.Texture2D.MipSlice = 0;
	device->CreateDepthStencilView(DepthStencilBuffer, &depthStencilViewDesc, &DepthStencilView);

	Viewport.Width = (float)width;
	Viewport.Height = (float)height;
	Viewport.MinDepth = 0.0f;
	Viewport.MaxDepth = 1.0f;
	Viewport.TopLeftX = 0.0f;
	Viewport.TopLeftY = 0.0f;

	return false;
}

void D3D11DeferredBuffer::Destroy(void)
{
	if (DepthStencilView)
		DepthStencilView->Release();

	if (DepthStencilBuffer)
		DepthStencilBuffer->Release();

	for (int i = 0; i < DEFERRED_RENDER_TARGET_TYPE_MAX; i++)
	{
		if (ShaderResourceViewArray[i])
			ShaderResourceViewArray[i]->Release();

		if (RenderTargetViewArray[i])
			RenderTargetViewArray[i]->Release();

		if (RenderTargetTextureArray[i])
			RenderTargetTextureArray[i]->Release();
	}
}

void D3D11DeferredBuffer::SetRenderTargets(ID3D11DeviceContext* context)
{
	context->OMSetRenderTargets(DEFERRED_RENDER_TARGET_TYPE_MAX, RenderTargetViewArray, DepthStencilView);
	context->RSSetViewports(1, &Viewport);
}

void D3D11DeferredBuffer::ClearRenderTargets(ID3D11DeviceContext* context, float* color)
{
	for (int index = 0; index < DEFERRED_RENDER_TARGET_TYPE_MAX; index++)
		context->ClearRenderTargetView(RenderTargetViewArray[index], color);
	context->ClearDepthStencilView(DepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
}

ID3D11ShaderResourceView* D3D11DeferredBuffer::GetShaderResourceView(int index)
{
	return ShaderResourceViewArray[index];
}

