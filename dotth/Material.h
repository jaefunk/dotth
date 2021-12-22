#pragma once

#include "Texture2D.h"
#include "Shader.h"

class Material : public Base
{
public:
	Material(void) = default;
	void Load(std::string texture, std::string vShader, std::string pShader);

private:
	std::shared_ptr<Texture2D> texture2D;
	std::shared_ptr<VertexShader> vertexShader;
	std::shared_ptr<PixelShader> pixelShader;

public:
	bool SetTexture(std::shared_ptr<Texture2D> newTexture)
	{
		if (newTexture == texture2D)
			return false;
		texture2D = newTexture;
		return true;
	}
	bool SetVertexShader(std::shared_ptr<VertexShader> newShader)
	{
		if (newShader == vertexShader)
			return false;
		vertexShader = newShader;
		return true;
	}
	bool SetPixelShader(std::shared_ptr<PixelShader> newShader)
	{
		if (newShader == pixelShader)
			return false;
		pixelShader = newShader;
		return true;
	}

public:
	void Bind(const XMFLOAT4X4& world, const XMFLOAT4X4& view, const XMFLOAT4X4& proj)
	{
		texture2D->Draw();

		vertexShader->SetMatrix4x4("world", world);
		vertexShader->SetMatrix4x4("view", view);
		vertexShader->SetMatrix4x4("projection", proj);
		vertexShader->CopyAllBufferData();
		vertexShader->SetShader();

		pixelShader->SetSamplerState("Sampler", D3D11RHI::Sampler());
		pixelShader->SetShaderResourceView("Texture", texture2D->GetShaderResourceView());
		pixelShader->CopyAllBufferData();
		pixelShader->SetShader();
	}
};