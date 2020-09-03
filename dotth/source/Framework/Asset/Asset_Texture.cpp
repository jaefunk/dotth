#include "Framework/Asset/Asset_Texture.h"

Asset_Texture::~Asset_Texture(void)
{
	_Resource->Release();
}

Asset_Texture::Asset_Texture(void) : Asset_Renderable(ASSET_TYPE::TEXTURE)
{

}

void Asset_Texture::Bind(void)
{
	Renderer::RHI()->PSSetShaderResource(0, 1, _ResourceView);
	Renderer::RHI()->PSSetSamplers();
}

bool Asset_Texture::OnLoad(void * data, size_t size)
{
	_Resource = Renderer::RHI()->CreateTexture2D(_Path.c_str());
	_ResourceView = Renderer::RHI()->CreateShaderResourceView(_Resource);

	return true;
}
