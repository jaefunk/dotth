
#pragma once

#include "dotth.h"

using namespace DirectX;
class D11RHI
{
public:
	bool Init(void* handle, int width, int height);
	void PreDraw(void);
	void PostDraw(void);
	bool Release(void);

public:
	ID3D11Buffer* CreateVertexBuffer(const D3D11_BUFFER_DESC& desc, const D3D11_SUBRESOURCE_DATA& data);
	ID3D11Buffer* CreateIndexBuffer(const D3D11_BUFFER_DESC& desc, const D3D11_SUBRESOURCE_DATA& data);
	ID3D11Buffer* CreateConstantBuffer(const D3D11_BUFFER_DESC& desc);
	ID3D11VertexShader* CreateVertexShader(ID3D10Blob* blob);
	ID3D11PixelShader* CreatePixelShader(ID3D10Blob* blob);
	ID3D11InputLayout* CreateInputLayout(ID3D10Blob* blob, D3D11_INPUT_ELEMENT_DESC* desc, unsigned int desc_size);
	void BindVertexBuffer(ID3D11Buffer* buffer, unsigned int stride, unsigned int offset);
	void BindIndexBuffer(ID3D11Buffer* buffer, DXGI_FORMAT format, unsigned int offset);
	void UpdateSubresource(ID3D11Buffer* buffer, void* data);
	void VSSetShader(ID3D11VertexShader* shader);
	void PSSetShader(ID3D11PixelShader* shader);
	void VSSetConstantBuffers(unsigned int start, unsigned int num, ID3D11Buffer* buffer);
	void PSSetConstantBuffers(unsigned int start, unsigned int num, ID3D11Buffer* buffer);
	void BindInputLayout(ID3D11InputLayout* input_layout);
	void Map(ID3D11Resource* resource, unsigned int subresource, D3D11_MAP map_type, unsigned int map_flags, D3D11_MAPPED_SUBRESOURCE* mapped_resources);
	void Unmap(ID3D11Resource* resource, unsigned int subresource);
	void DrawIndexed(unsigned int size, unsigned int start, unsigned int base);

	ID3D11Resource* CreateTexture2D(const char* file_name);
	ID3D11ShaderResourceView* CreateShaderResourceView(ID3D11Resource* resource);
	void PSSetShaderResource(unsigned int start, unsigned int num, ID3D11ShaderResourceView* resource_view);
	void PSSetSamplers(void);

private:
	ID3D11Device* _Device = nullptr;
	ID3D11DeviceContext* _Context = nullptr;
	IDXGISwapChain* _SwapChain = nullptr;
	ID3D11RenderTargetView* _RenderTargetView = nullptr;
	ID3D11DepthStencilView* _DepthBuffer = nullptr;
	ID3D11RasterizerState* _RasterizerState = nullptr;
	ID3D11SamplerState* _SamplerState = nullptr;
};

// D11RHI