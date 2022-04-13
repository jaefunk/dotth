#pragma once

#include "D3D11.h"
#include "D3D11Renderable.h"

enum GBUFFER_TYPE {
	GBUFFER_TYPE_DIFFUSE,
	GBUFFER_TYPE_NORMAL,
	GBUFFER_TYPE_MAX,
};

struct D3D11GBuffer {
	ID3D11RenderTargetView* renderTargetView = nullptr;
	ID3D11ShaderResourceView* shaderResourceView = nullptr;

	D3D11GBuffer(ID3D11Device* pDevice, DXGI_FORMAT format, uint32_t width, uint32_t height)
	{
		ID3D11Texture2D* renderTargetTexture;
		
		D3D11::CreateTexture2D(width, height, 1, 1, format, 1, 0, D3D11_USAGE_DEFAULT, D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE, 0, 0, pDevice, &renderTargetTexture);
		D3D11_RENDER_TARGET_VIEW_DESC renderTargetViewDesc;
		renderTargetViewDesc.Format = format;
		renderTargetViewDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
		renderTargetViewDesc.Texture2D.MipSlice = 0;
		D3D11::CreateRenderTargetView(renderTargetTexture, &renderTargetViewDesc, pDevice, &renderTargetView);
		D3D11_SHADER_RESOURCE_VIEW_DESC shaderResourceViewDesc;
		shaderResourceViewDesc.Format = format;
		shaderResourceViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		shaderResourceViewDesc.Texture2D.MostDetailedMip = 0;
		shaderResourceViewDesc.Texture2D.MipLevels = 1;
		D3D11::CreateShaderResourceView(renderTargetTexture, &shaderResourceViewDesc, pDevice, &shaderResourceView);

		renderTargetTexture->Release();
	}
};

class D3D11DefferedRenderSystem 
{
public:
	void Initialize(ID3D11Device* pDevice, ID3D11DeviceContext* pContext, uint32_t width, uint32_t height)
	{
		GBuffers[GBUFFER_TYPE_DIFFUSE] = new D3D11GBuffer(pDevice, DXGI_FORMAT_R32G32B32A32_FLOAT, width, height);
		GBuffers[GBUFFER_TYPE_NORMAL] = new D3D11GBuffer(pDevice, DXGI_FORMAT_R32G32B32A32_FLOAT, width, height);

		float left = ((float)width / 2.f) * -1.f;
		float right = left + (float)width;
		float top = (float)height * 0.5f;
		float bottom = top - (float)height;
		std::vector<dotth::vector3> positions = { {left, top, 0.f}, {right, top, 0.f}, {left, bottom, 0.f}, {right, bottom, 0.f} };
		std::vector<dotth::vector2> textureCoords = { {0.f, 0.f}, {1.f, 0.f}, {0.f, 1.f}, {1.f, 1.f} };	
		std::vector<unsigned int> indices = { 0, 1, 2, 1, 3, 2 };
		view = new D3D11Renderable(pDevice, pContext);
		view->AddVertexBuffer(positions.data(), sizeof(dotth::vector3), static_cast<unsigned int>(positions.size()));
		view->AddVertexBuffer(textureCoords.data(), sizeof(dotth::vector2), static_cast<unsigned int>(textureCoords.size()));
		view->SetIndexBuffer(indices.data(), sizeof(unsigned int), static_cast<unsigned int>(indices.size()));
		view->LoadVertexShader("../Output/Client/x64/Debug/light_vs.cso");
		view->LoadPixelShader("../Output/Client/x64/Debug/light_ps.cso");
	}

	void CommitRenderTarget(ID3D11DeviceContext* pContext, ID3D11DepthStencilView* pDepthStencilView)
	{
		ID3D11RenderTargetView* GBufferArray[GBUFFER_TYPE_MAX];
		for (uint32_t index = 0; index < GBUFFER_TYPE_MAX; ++index)// = D3D11GBuffer* buffer : GBuffers)
		{
			GBufferArray[index] = GBuffers[index]->renderTargetView;
		}
		pContext->OMSetRenderTargets(GBUFFER_TYPE_MAX, GBufferArray, pDepthStencilView);
	}

	void ClearRenderTarget(ID3D11DeviceContext* pContext, float* color)
	{
		for (uint32_t index = 0; index < GBUFFER_TYPE_MAX; index++)
		{
			pContext->ClearRenderTargetView(GBuffers[index]->renderTargetView, color);
		}
	}

	void Draw(void)
	{
		view->Draw();
	}

private:
	D3D11GBuffer* GBuffers[GBUFFER_TYPE_MAX];
	D3D11Renderable* view;
};

#include "dotth.h"

enum DEFERRED_RENDER_TARGET_TYPE {
	POSITION,
	DIFFUSE,
	NORMAL,
	DEFERRED_RENDER_TARGET_TYPE_MAX,
};

class D3D11DeferredBuffer
{
public:
	D3D11DeferredBuffer();
	~D3D11DeferredBuffer();
	bool Initialize(ID3D11Device* device, unsigned int width, unsigned int height);
	void Destroy(void);
	void SetRenderTargets(ID3D11DeviceContext* context);
	void ClearRenderTargets(ID3D11DeviceContext* context, float* color);
	ID3D11ShaderResourceView* GetShaderResourceView(int index);

private:
	ID3D11Texture2D* RenderTargetTextureArray[DEFERRED_RENDER_TARGET_TYPE_MAX];
	ID3D11RenderTargetView* RenderTargetViewArray[DEFERRED_RENDER_TARGET_TYPE_MAX];
	ID3D11ShaderResourceView* ShaderResourceViewArray[DEFERRED_RENDER_TARGET_TYPE_MAX];
	ID3D11Texture2D* DepthStencilBuffer = nullptr;
	ID3D11DepthStencilView* DepthStencilView = nullptr;
	D3D11_VIEWPORT Viewport;
};