#pragma once

#include "dotth.h"

namespace D3D11 
{
	void CreateDevice(
		ID3D11Device** ppDevice, 
		ID3D11DeviceContext** ppDeviceContext);
	
	void CreateSwapChain(
		void* handle,  
		uint32_t width, 
		uint32_t height, 
		ID3D11Device* pDevice, 
		IDXGISwapChain** ppSwapChain);

	void CreateTexture2D(
		uint32_t width,
		uint32_t height,
		uint32_t mipLevels,
		uint32_t arraySize,
		DXGI_FORMAT format,
		uint32_t sampleCount,
		uint32_t sampleQuality,
		D3D11_USAGE usage,
		uint32_t bindFlags,
		uint32_t cpuAccessFlags,
		uint32_t miscFlags,
		ID3D11Device* pDevice,
		ID3D11Texture2D** ppTexture2D);

	void CreateDepthStencilState(
		ID3D11Device* pDevice, 
		ID3D11DepthStencilState** ppDepthStencilState);

	void CreateDepthStencilView(
		ID3D11Device* pDevice, 
		ID3D11Texture2D* pDepthStencilTexture, 
		ID3D11DepthStencilView** ppDepthStencilView);

	void CreateRasterizerState(
		D3D11_FILL_MODE fillMode,
		D3D11_CULL_MODE cullMode,
		bool multiSampleEnable,
		ID3D11Device* pDevice, 
		ID3D11RasterizerState** ppRasterrizerState);

	void CreateSamplerState(
		D3D11_TEXTURE_ADDRESS_MODE addressU,
		D3D11_TEXTURE_ADDRESS_MODE addressV,
		D3D11_TEXTURE_ADDRESS_MODE addressW,
		ID3D11Device* pDevice,
		ID3D11SamplerState** ppSamplerState);

	void CreateRenderTargetView(
		IDXGISwapChain* pSwapChain, 
		ID3D11Device* pDevice, 
		ID3D11RenderTargetView** ppRenderTargetView);

	void CreateRenderTargetView(
		ID3D11Resource* pResource,
		D3D11_RENDER_TARGET_VIEW_DESC* pDesc,
		ID3D11Device* pDevice,
		ID3D11RenderTargetView** ppRenderTargetView);

	void CreateShaderResourceView(
		ID3D11Resource* pResource, 
		D3D11_SHADER_RESOURCE_VIEW_DESC* pDesc,
		ID3D11Device* pDevice,
		ID3D11ShaderResourceView** ppShaderResourceView);

}