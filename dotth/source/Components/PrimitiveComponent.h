
#pragma once

#include "Components/DrawableComponent.h"
#include "Graphics/shader.h"

struct MatrixBufferType
{
	XMMATRIX world;
	XMMATRIX view;
	XMMATRIX projection;
};

class PrimitiveComponent : public DrawableComponent
{
public:
	ID3D11Buffer* _ConstantBuffer = nullptr;
	Shader _Shader;

	virtual unsigned int GetVertexStructureSize(void) = 0;
	virtual unsigned int GetVertexCount(void) = 0;
	virtual unsigned int GetIndexCount(void) = 0;
	virtual void* GetVertexArray(void) = 0;
	virtual unsigned long* GetIndexArray(void) = 0;
	virtual std::string GetShaderName(void) = 0;
	virtual void GetInputDesc(D3D11_INPUT_ELEMENT_DESC** desc, unsigned int& size) = 0;
	
public:
	virtual void OnInit(void) override;

	virtual void OnUpdate(void) override;

	virtual void OnDraw(void) override;
};

