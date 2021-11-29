#pragma once

#include "Texture2D.h"
#include "Shader.h"

class Material
{
private:
	std::shared_ptr<Texture2D> texture2D;
	std::shared_ptr<VertexShader> deferredVertexShader;
	std::shared_ptr<PixelShader> deferredPixelShader;

public:
	bool SetTexture(std::shared_ptr<Texture2D> newTexture)
	{
		if (newTexture == texture2D)
		{
			return false;
		}
		texture2D = newTexture;
		return true;
	}
};