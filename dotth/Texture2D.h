#pragma once

#include "D3D11RHI.h"

class Texture2D
{
private:
	ID3D11SamplerState* samplerState = nullptr;
	ID3D11Resource* resource = nullptr;
	ID3D11ShaderResourceView* shaderResourceView = nullptr;

public:
	ID3D11ShaderResourceView* GetShaderResourceView(void);
	bool Load(const std::string& key);
	void Draw(void);
};