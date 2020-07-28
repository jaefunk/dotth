
#pragma once

#include "graphics/shader.h"

class shader_color : public shader
{
private:
	struct MatrixBufferType
	{
		XMMATRIX world;
		XMMATRIX view;
		XMMATRIX projection;
	};
protected:
	virtual std::vector<D3D11_INPUT_ELEMENT_DESC> get_input_layout(void) 
	{
		std::vector<D3D11_INPUT_ELEMENT_DESC> layout_list;

		layout_list.emplace_back();
		layout_list.back().SemanticName = "POSITION";
		layout_list.back().SemanticIndex = 0;
		layout_list.back().Format = DXGI_FORMAT_R32G32B32_FLOAT;
		layout_list.back().InputSlot = 0;
		layout_list.back().AlignedByteOffset = 0;
		layout_list.back().InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		layout_list.back().InstanceDataStepRate = 0;

		layout_list.emplace_back();
		layout_list.back().SemanticName = "COLOR";
		layout_list.back().SemanticIndex = 0;
		layout_list.back().Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		layout_list.back().InputSlot = 0;
		layout_list.back().AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
		layout_list.back().InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		layout_list.back().InstanceDataStepRate = 0;	

		return layout_list;
	}

	virtual D3D11_BUFFER_DESC get_matrix_buffer_desc(void)
	{
		D3D11_BUFFER_DESC desc;
		desc.Usage = D3D11_USAGE_DYNAMIC;
		desc.ByteWidth = sizeof(MatrixBufferType);
		desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		desc.MiscFlags = 0;
		desc.StructureByteStride = 0;
	}
	
	virtual void pre_reset(void) 
	{
	}
	
	virtual void post_reset(void) 
	{
	}
};