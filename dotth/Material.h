#pragma once

#include "AssetBase.h"
#include "Texture2D.h"
#include "Shader.h"


struct SkeletalMeshRenderParameter
{
	std::string name;
	void* value;
	unsigned int size;
};

class Material : public Base
{
public:
	Material(void);
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
	std::shared_ptr<VertexShader> GetVS(void)
	{
		return vertexShader;
	}

public:
	void Bind(std::vector<SkeletalMeshRenderParameter> parameters)
	{
		if (texture2D)
			texture2D->Draw();

		for (auto parameter : parameters)
		{
			vertexShader->SetData(parameter.name, parameter.value, parameter.size);
		}
		vertexShader->CopyAllBufferData();
		vertexShader->SetShader();
		
		pixelShader->SetSamplerState("Sampler", D3D11RHI::Sampler());
		pixelShader->SetShaderResourceView("Texture", texture2D->GetShaderResourceView());
		pixelShader->CopyAllBufferData();
		pixelShader->SetShader();
	}
};