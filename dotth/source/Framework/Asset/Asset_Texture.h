#pragma once

#include "Framework/Asset/Asset_Renderable.h"
#include "Graphics/Renderer.h"

class Asset_Texture : public Asset_Renderable
{
private:
	ID3D11Resource* _Resource = nullptr;
	ID3D11ShaderResourceView* _ResourceView = nullptr;

public:
	virtual ~Asset_Texture(void);

public:
	Asset_Texture(void);

public:
	virtual void Bind(void) override;

private:
	virtual bool OnLoad(void* data, size_t size) override;
};