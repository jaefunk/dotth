#pragma once

#include "AssetBase.h"

class Texture2D : public Texture
{
private:
	ID3D11SamplerState* samplerState = nullptr;
	ID3D11Resource* resource = nullptr;
	ID3D11ShaderResourceView* shaderResourceView = nullptr;

public:
	ID3D11ShaderResourceView* GetShaderResourceView(void);
	bool Load(const std::string& key);
	void Draw(unsigned int index);
};