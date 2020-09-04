#pragma once

#include "Framework/Asset/Asset.h"
#include "Graphics/Renderer.h"

class Asset_Renderable : public Asset
{
public:
	Asset_Renderable(ASSET_TYPE type);

public:
	virtual void Bind(void);
};