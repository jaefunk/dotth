
#pragma once

#include "Shader.h"

class PrimitiveShader : public Shader
{
public:
	void Draw(ID3D11Buffer* buffer)
	{
		
		Renderer::RHI()->VSSetConstantBuffers(0, 1, buffer);
		Renderer::RHI()->BindInputLayout(_InputLayout);
		Renderer::RHI()->VSSetShader(_VertexShader);
		Renderer::RHI()->PSSetShader(_PixelShader);
		//Renderer::RHI()->PSSetConstantBuffers(0, 1, buffer);
		Renderer::RHI()->DrawIndexed(36, 0, 0);

	}
};