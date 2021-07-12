﻿
#include "D3D11Texture2D.h"

void D3D11Texture2D::Load(const std::string& path)
{
	LoadJpeg(path);

	_Texture2D = nullptr;

	D3D11_TEXTURE2D_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.Width = width;
	desc.Height = height;
	desc.MipLevels = desc.ArraySize = 1;
	desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.SampleDesc.Count = 1;
	desc.Usage = D3D11_USAGE_IMMUTABLE;
	desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	//desc.CPUAccessFlags = 0;
	//desc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA initData;
	ZeroMemory(&initData, sizeof(initData));
	initData.pSysMem = texels.data();
	initData.SysMemPitch = sizeof(r8g8b8a8) * width;
	initData.SysMemSlicePitch = 0;
	D3D11RHI::Device()->CreateTexture2D(&desc, &initData, (ID3D11Texture2D**)&_Texture2D);

	D3D11_SHADER_RESOURCE_VIEW_DESC SRVDesc;
	ZeroMemory(&SRVDesc, sizeof(SRVDesc));
	SRVDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	SRVDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	SRVDesc.Texture2D.MipLevels = 1;
	D3D11RHI::Device()->CreateShaderResourceView(_Texture2D, &SRVDesc, &_ShaderResourceView);

}

void D3D11Texture2D::Draw(const unsigned int& index)
{
	D3D11RHI::Context()->PSSetShaderResources(0, 1, &_ShaderResourceView);
	//ID3D11SamplerState* jj = D3D11RHI::Sampler();
	//D3D11RHI::Context()->PSSetSamplers(0, 1, &jj);
}