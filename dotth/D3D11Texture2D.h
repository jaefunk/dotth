#pragma once

#include "D3D11RHI.h"
#include "Texture2D.h"

class D3D11Texture2D : public Texture2D
{
private:
	ID3D11SamplerState* _SamplerState = nullptr;
	ID3D11Resource* _Texture2D = nullptr;
	ID3D11ShaderResourceView* _ShaderResourceView = nullptr;

public:
	void Load(const std::string& key);
	virtual void Draw(const unsigned int& index) override;
};