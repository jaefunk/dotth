
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
	virtual unsigned int GetVertexStructureSize(void)
	{
		return sizeof(VertexPNU);
	}
	virtual unsigned int GetVertexCount(void)
	{
		return _Model->_VertexCount;
	}
	virtual unsigned int GetIndexCount(void)
	{
		return _Model->_IndexCount;
	}
	virtual void* GetVertexArray(void)
	{
		return _Model->_Meshes[0]._Vertices.data();
	}
	virtual unsigned long* GetIndexArray(void)
	{
		return _Model->_Meshes[0]._Indices.data();
	};
	virtual std::string GetShaderName(void)
	{
		return "Resource/Model.fx";
	}
	virtual void GetInputDesc(D3D11_INPUT_ELEMENT_DESC** desc, unsigned int& size)
	{
		(*desc) = new D3D11_INPUT_ELEMENT_DESC[2];
		(*desc)[0] = { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 };
		//(*desc)[1] = { "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 };
		(*desc)[1] = { "TEXCOORD0", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 };
		size = 2;
	}

public:
	virtual void OnUpdate(void) override;
	virtual void OnDraw(void) override;
	virtual void OnDestroy(void) override;
};