
#include "SpriteComponent.h"

SpriteComponent::SpriteComponent(const char * asset)
{
	_Texture = std::static_pointer_cast<Asset_Texture>(AssetManager::Instance()->FindOrigin(asset));
}

void SpriteComponent::GetInputDesc(D3D11_INPUT_ELEMENT_DESC ** desc, unsigned int & size)
{
	(*desc) = new D3D11_INPUT_ELEMENT_DESC[2];
	(*desc)[0] = { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 };
	(*desc)[1] = { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 };
	size = 2;
}

unsigned int SpriteComponent::GetVertexStructureSize(void)
{
	return sizeof(pos_uv);
}

unsigned int SpriteComponent::GetVertexCount(void)
{
	return 4;
}

unsigned int SpriteComponent::GetIndexCount(void)
{
	return 6;
}

void * SpriteComponent::GetVertexArray(void)
{
	pos_uv* vertices = new pos_uv[GetVertexCount()];

	vertices[0] = { XMFLOAT3(-1.0f, +1.0f, +0.0f),  XMFLOAT2(0.0f, 0.0f) };
	vertices[1] = { XMFLOAT3(+1.0f, +1.0f, +0.0f),  XMFLOAT2(1.0f, 0.0f) };
	vertices[2] = { XMFLOAT3(-1.0f, -1.0f, +0.0f),  XMFLOAT2(0.0f, 1.0f) };
	vertices[3] = { XMFLOAT3(+1.0f, -1.0f, +0.0f),  XMFLOAT2(1.0f, 1.0f) };

	return vertices;
}

unsigned long * SpriteComponent::GetIndexArray(void)
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

std::string SpriteComponent::GetShaderName(void)
{
	return "Resource/Texture.fx";
}

void SpriteComponent::OnDraw(void)
{
	Renderer::RHI()->BindVertexBuffer(_VertexBuffer, GetVertexStructureSize(), 0);
	Renderer::RHI()->BindIndexBuffer(_IndexBuffer, DXGI_FORMAT_R32_UINT, 0);

	MatrixBufferType cb;
	cb.view = DirectX::XMMatrixTranspose(*Camera::Instance()->View());
	cb.projection = DirectX::XMMatrixTranspose(*Camera::Instance()->Perspective());
	cb.world = DirectX::XMMatrixIdentity();

	Renderer::RHI()->UpdateSubresource(_ConstantBuffer, &cb);

	_Texture->Bind();

	_Shader2.Draw(_ConstantBuffer, GetIndexCount());
}
