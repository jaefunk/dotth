#pragma once

#include "Framework/Asset/Asset.h"
#include "Graphics/Renderer.h"

class Asset_Texture2D : public Asset
{
private:
	ID3D11Resource* _Resource = nullptr;
	ID3D11ShaderResourceView* _ResourceView = nullptr;

public:
	virtual ~Asset_Texture2D(void)
	{
		_Resource->Release();
	}

public:
	Asset_Texture2D(void) : Asset(ASSET_TYPE::TEXTURE2D)
	{
		
	}

public:
	void BindTexture(void)
	{
		Renderer::RHI()->PSSetShaderResource(0, 1, _ResourceView);
		Renderer::RHI()->PSSetSamplers();
	}

private:
	virtual bool OnLoad(const char* data, long length) override
	{
		_Resource = Renderer::RHI()->CreateTexture2D((void*)data, length);
		_ResourceView = Renderer::RHI()->CreateShaderResourceView(_Resource);
		
		return true;
	}
};