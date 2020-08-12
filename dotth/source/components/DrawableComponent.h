#pragma once

#include "Framework/Component.h"
#include "Graphics/Renderer.h"

template <class VertexType, class ShaderType>
class DrawableComponent : public Component
{
protected:
	ID3D11Buffer* _VertexBuffer = nullptr;
	ID3D11Buffer* _IndexBuffer = nullptr;
	ID3D11InputLayout* _InputLayout = nullptr;
	ID3D11VertexShader* _VertexShader = nullptr;
	ID3D11PixelShader* _PixelShader = nullptr;


	VertexBufferRHI* VertexBuffer = nullptr;
	IndexBufferRHI* IndexBuffer = nullptr;	
	VertexShaderRHI* VertexShader = nullptr;
	PixelShaderRHI* PixelShader = nullptr;
	InputLayoutRHI* InputLayout = nullptr;

public:
	virtual ~DrawableComponent(void)
	{
		if (VertexBuffer)
		{
			VertexBuffer->Release();
			delete VertexBuffer;
			VertexBuffer = nullptr;
		}
		if (IndexBuffer)
		{
			IndexBuffer->Release();
			delete IndexBuffer;
			IndexBuffer = nullptr;
		}

		if (_VertexBuffer)
			_VertexBuffer->Release();
		if (_IndexBuffer)
			_IndexBuffer->Release();
		if (_InputLayout)
			_InputLayout->Release();
		if (_VertexShader)
			_VertexShader->Release();
		if (_PixelShader)
			_PixelShader->Release();
	}
};

