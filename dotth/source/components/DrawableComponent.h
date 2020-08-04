#pragma once

#include "Framework/Component.h"
#include "Graphics/Renderer.h"

class DrawableComponent : public Component
{
	/*
	ID3D11DeviceContext*                g_pImmediateContext = NULL;
	ID3D11Texture2D*                    g_pDepthStencil = NULL;
	ID3D11VertexShader*                 g_pVertexShader = NULL;
	ID3D11PixelShader*                  g_pPixelShader = NULL;
	ID3D11InputLayout*                  g_pVertexLayout = NULL;
	ID3D11Buffer*                       g_pVertexBuffer = NULL;
	ID3D11Buffer*                       g_pIndexBuffer = NULL;
	ID3D11Buffer*                       g_pCBNeverChanges = NULL;
	ID3D11Buffer*                       g_pCBChangeOnResize = NULL;
	ID3D11Buffer*                       g_pCBChangesEveryFrame = NULL;
	ID3D11ShaderResourceView*           g_pTextureRV = NULL;
	ID3D11SamplerState*                 g_pSamplerLinear = NULL;

	*/
protected:
	VertexBufferRHI* VertexBuffer = nullptr;
	IndexBufferRHI* IndexBuffer = nullptr;

public:
	virtual ~DrawableComponent(void)
	{
		if (VertexBuffer)
		{
			VertexBuffer->Release();
			delete VertexBuffer;
			VertexBuffer = nullptr;
		}
		if (IndexBuffer)
		{
			IndexBuffer->Release();
			delete IndexBuffer;
			IndexBuffer = nullptr;
		}
	}
};

