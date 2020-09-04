
#pragma once

#include "Components/PrimitiveComponent.h"

struct VertexType
{
	XMFLOAT3 position;
	XMFLOAT4 color;
};

class CubeComponent : public PrimitiveComponent
{
public:
	virtual void GetInputDesc(D3D11_INPUT_ELEMENT_DESC** desc, unsigned int& size) override;
	virtual unsigned int GetVertexStructureSize(void) override;

	virtual unsigned int GetVertexCount(void) override;
	virtual unsigned int GetIndexCount(void) override;
	virtual void* GetVertexArray(void) override;
	virtual unsigned long* GetIndexArray(void) override;
	virtual std::string GetShaderName(void) override;
};