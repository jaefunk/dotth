#pragma once

#include "dotth.h"
#include "D3D11RHI.h"

class D3D11Shader
{
public:

	void Draw(ID3D11Buffer* buffer, unsigned int size)
	{
		//Renderer::RHI()->VSSetConstantBuffers(0, 1, buffer);
		//Renderer::RHI()->BindInputLayout(_InputLayout);
		//Renderer::RHI()->VSSetShader(_VertexShader);
		//Renderer::RHI()->PSSetShader(_PixelShader);
		//Renderer::RHI()->DrawIndexed(size, 0, 0);
	}
};