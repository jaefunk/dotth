
#include "Material.h"

void Material::Load(std::string texture, std::string vShader, std::string pShader)
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
}