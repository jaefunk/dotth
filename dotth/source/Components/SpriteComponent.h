
#pragma once

#include "Components/PrimitiveComponent.h"
#include "Framework/Asset/Asset_Texture.h"

struct pos_uv
{
	XMFLOAT3 position;
	XMFLOAT2 uv;
};

class SpriteComponent : public PrimitiveComponent
{
public:
	SpriteComponent(const char* asset);

private:
	std::shared_ptr<Asset_Texture> _Texture;

public:
	virtual void GetInputDesc(D3D11_INPUT_ELEMENT_DESC** desc, unsigned int& size) override;
	virtual unsigned int GetVertexStructureSize(void) override;
	virtual unsigned int GetVertexCount(void) override;
	virtual unsigned int GetIndexCount(void) override;
	virtual void* GetVertexArray(void) override;
	virtual unsigned long* GetIndexArray(void) override;
	virtual std::string GetShaderName(void) override;

	virtual void OnDraw(void) override;
};