
#include "AssetBase.h"
#include "ResourceManager.h"

#include "Texture2D.h"

bool Texture2D::Load(const std::string& key)
{
	std::shared_ptr<dotth::texture> base = ResourceManager2::Find<dotth::texture>(key);
	if (base == nullptr)
		return false;
	D3D11_TEXTURE2D_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.Width = base->width;
	desc.Height = base->height;
	desc.MipLevels = desc.ArraySize = 1;
	desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.SampleDesc.Count = 1;
	desc.Usage = D3D11_USAGE_IMMUTABLE;
	desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	//desc.CPUAccessFlags = 0;
	//desc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA initData;
	ZeroMemory(&initData, sizeof(initData));
	initData.pSysMem = base->data();
	initData.SysMemPitch = base->pitch();
	initData.SysMemSlicePitch = 0;
	D3D11RHI::Device()->CreateTexture2D(&desc, &initData, (ID3D11Texture2D**)&resource);

	D3D11_SHADER_RESOURCE_VIEW_DESC SRVDesc;
	ZeroMemory(&SRVDesc, sizeof(SRVDesc));
	SRVDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	SRVDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	SRVDesc.Texture2D.MipLevels = 1;
	D3D11RHI::Device()->CreateShaderResourceView(resource, &SRVDesc, &shaderResourceView);

	return true;
}

void Texture2D::Draw(void)
{
	D3D11RHI::Context()->PSSetShaderResources(0, 1, &shaderResourceView);
}

ID3D11ShaderResourceView* Texture2D::GetShaderResourceView(void)
{
	return shaderResourceView;
}