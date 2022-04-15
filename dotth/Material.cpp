
#include "Material.h"

Material::Material(void)
{
	Load("uv_checker", 
		"../Output/Client/x64/Debug/deferred_vs.cso", 
		"../Output/Client/x64/Debug/deferred_ps.cso",
		"");
}

void Material::Load(std::string texture, std::string vShader, std::string pShader, std::string gShader)
{
	if (texture2D == nullptr)
		texture2D = std::make_shared<Texture2D>();
	texture2D->Load(texture);

	std::wstring vShader_w;
	vShader_w.assign(vShader.begin(), vShader.end());
	if (vertexShader == nullptr)
		vertexShader = std::make_shared<VertexShader>(D3D11RHI::Device(), D3D11RHI::Context());
	vertexShader->LoadShaderFile(vShader_w.c_str());

	std::wstring pShader_w;
	pShader_w.assign(pShader.begin(), pShader.end());
	if (pixelShader == nullptr)
		pixelShader = std::make_shared<PixelShader>(D3D11RHI::Device(), D3D11RHI::Context());
	pixelShader->LoadShaderFile(pShader_w.c_str());

	if (gShader.length() > 0)
	{
		std::wstring gShader_w;
		gShader_w.assign(gShader.begin(), gShader.end());
		if (geometryShader == nullptr)
			geometryShader = std::make_shared<GeometryShader>(D3D11RHI::Device(), D3D11RHI::Context());
		geometryShader->LoadShaderFile(gShader_w.c_str());
	}
}

bool Material::SetTexture(std::shared_ptr<Texture2D> newTexture)
{
	if (newTexture == texture2D)
		return false;
	texture2D = newTexture;
	return true;
}

bool Material::SetVertexShader(std::shared_ptr<VertexShader> newShader)
{
	if (newShader == vertexShader)
		return false;
	vertexShader = newShader;
	return true;
}

bool Material::SetPixelShader(std::shared_ptr<PixelShader> newShader)
{
	if (newShader == pixelShader)
		return false;
	pixelShader = newShader;
	return true;
}

void Material::Bind(std::vector<MeshRenderParameter> parameters)
{
	if (texture2D)
		texture2D->Draw();

	for (auto parameter : parameters)
	{
		vertexShader->SetData(parameter.name, parameter.value, parameter.size);
	}
	vertexShader->CopyAllBufferData();
	vertexShader->SetShader();

	//if (geometryShader)
	//{
	//	geometryShader->CopyAllBufferData();
	//	geometryShader->SetShader();
	//}

	pixelShader->SetSamplerState("Sampler", D3D11RHI::Sampler());
	pixelShader->SetShaderResourceView("Texture", texture2D->GetShaderResourceView());
	pixelShader->CopyAllBufferData();
	pixelShader->SetShader();
}
