
#pragma once

#include "Components/PrimitiveComponent.h"
#include "Framework/Asset/Asset_Model.h"
#include "Framework/Asset/Asset_Texture.h"

class ModelComponent : public PrimitiveComponent
{
public:
	ModelComponent(const char* asset = nullptr);

private:
	std::shared_ptr<Asset_Model> _Model;
	std::shared_ptr<Asset_Texture> _Texture;

public:
	virtual unsigned int GetVertexStructureSize(void);
	virtual unsigned int GetVertexCount(void);
	virtual unsigned int GetIndexCount(void);
	virtual void* GetVertexArray(void);
	virtual unsigned long* GetIndexArray(void);;
	virtual std::string GetShaderName(void);
	virtual void GetInputDesc(D3D11_INPUT_ELEMENT_DESC** desc, unsigned int& size);

public:
	virtual void OnUpdate(void) override;
	virtual void OnDraw(void) override;
	virtual void OnDestroy(void) override;
};