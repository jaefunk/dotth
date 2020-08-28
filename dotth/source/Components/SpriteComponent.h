
#pragma once

#include "Components/PrimitiveComponent.h"
#include "../Framework/Asset/Asset_Texture2D.h"

struct pos_uv
{
	XMFLOAT3 position;
	XMFLOAT2 uv;
};

class SpriteComponent : public PrimitiveComponent
{
private:
	Asset_Texture2D* texture;

public:
	virtual void GetInputDesc(D3D11_INPUT_ELEMENT_DESC** desc, unsigned int& size) override
	{
		texture = new Asset_Texture2D;
		texture->Load("test.png");
		(*desc) = new D3D11_INPUT_ELEMENT_DESC[2];
		(*desc)[0] = { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 };
		(*desc)[1] = { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 };
		size = 2;
	}
	virtual unsigned int GetVertexStructureSize(void) override
	{
		return sizeof(pos_uv);
	}
	virtual unsigned int GetVertexCount(void) override
	{
		return 4;
	}
	virtual unsigned int GetIndexCount(void) override
	{
		return 6;
	}
	virtual void* GetVertexArray(void) override
	{
		pos_uv* vertices = new pos_uv[GetVertexCount()];

		vertices[0] = { XMFLOAT3(-1.0f, +1.0f, +0.0f),  XMFLOAT2(0.0f, 0.0f) };
		vertices[1] = { XMFLOAT3(+1.0f, +1.0f, +0.0f),  XMFLOAT2(1.0f, 0.0f) };
		vertices[2] = { XMFLOAT3(-1.0f, -1.0f, +0.0f),  XMFLOAT2(0.0f, 1.0f) };
		vertices[3] = { XMFLOAT3(+1.0f, -1.0f, +0.0f),  XMFLOAT2(1.0f, 1.0f) };

		return vertices;
	}
	virtual unsigned long* GetIndexArray(void) override
	{
		unsigned long* indices = new unsigned long[GetIndexCount()];

		indices[0] = 0;
		indices[1] = 1;
		indices[2] = 2;
		indices[3] = 1;
		indices[4] = 3;
		indices[5] = 2;

		return indices;
	}
	virtual std::string GetShaderName(void) override
	{
		return "Resource/Texture.fx";
	}

	virtual void OnDraw(void) override
	{
		Renderer::RHI()->BindVertexBuffer(_VertexBuffer, GetVertexStructureSize(), 0);
		Renderer::RHI()->BindIndexBuffer(_IndexBuffer, DXGI_FORMAT_R32_UINT, 0);

		MatrixBufferType cb;
		cb.view = DirectX::XMMatrixTranspose(*Camera::Instance()->View());
		cb.projection = DirectX::XMMatrixTranspose(*Camera::Instance()->Perspective());
		cb.world = DirectX::XMMatrixIdentity();
		
		Renderer::RHI()->UpdateSubresource(_ConstantBuffer, &cb);

		texture->BindTexture();

		_Shader.Draw(_ConstantBuffer, GetIndexCount());
	}
};