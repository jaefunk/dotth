
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
	//ID3D11Device* Device(void) {
	//	return _Device;
	//}
	//ID3D11DeviceContext* Context(void) {
	//	return _Context; 
	//}

	ID3D11Buffer* CreateVertexBuffer(const D3D11_BUFFER_DESC& desc, const D3D11_SUBRESOURCE_DATA& data)
	{
		ID3D11Buffer* buffer = nullptr;
		_Device->CreateBuffer(&desc, &data, &buffer);
		return buffer;
	}
	ID3D11Buffer* CreateIndexBuffer(const D3D11_BUFFER_DESC& desc, const D3D11_SUBRESOURCE_DATA& data)
	{
		ID3D11Buffer* buffer = nullptr;
		_Device->CreateBuffer(&desc, &data, &buffer);
		return buffer;
	}
	ID3D11Buffer* CreateConstantBuffer(const D3D11_BUFFER_DESC& desc)
	{
		ID3D11Buffer* buffer = nullptr;
		_Device->CreateBuffer(&desc, NULL, &buffer);
		return buffer;
	}
	ID3D11VertexShader* CreateVertexShader(ID3D10Blob* blob)
	{
		ID3D11VertexShader* shader = nullptr;
		_Device->CreateVertexShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, &shader);
		return shader;
	}
	ID3D11PixelShader* CreatePixelShader(ID3D10Blob* blob)
	{
		ID3D11PixelShader* shader = nullptr;
		_Device->CreatePixelShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, &shader);
		return shader;
	}
	ID3D11InputLayout* CreateInputLayout(ID3D10Blob* blob, D3D11_INPUT_ELEMENT_DESC* desc, unsigned int desc_size)
	{
		ID3D11InputLayout* layout = nullptr;
		_Device->CreateInputLayout(desc, desc_size, blob->GetBufferPointer(), blob->GetBufferSize(), &layout);
		return layout;
	}
	void BindVertexBuffer(ID3D11Buffer* buffer, unsigned int stride, unsigned int offset)
	{
		_Context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		_Context->IASetVertexBuffers(0, 1, &buffer, &stride, &offset);
	}
	void BindIndexBuffer(ID3D11Buffer* buffer, DXGI_FORMAT format, unsigned int offset)
	{
		_Context->IASetIndexBuffer(buffer, format, offset);
	}
	void UpdateSubresource(ID3D11Buffer* buffer, void* data)
	{
		_Context->UpdateSubresource(buffer, 0, nullptr, data, 0, 0);
	}
	void VSSetShader(ID3D11VertexShader* shader)
	{
		_Context->VSSetShader(shader, nullptr, 0);
	}
	void PSSetShader(ID3D11PixelShader* shader)
	{
		_Context->PSSetShader(shader, nullptr, 0);
	}
	void VSSetConstantBuffers(unsigned int start, unsigned int num, ID3D11Buffer* buffer)
	{
		_Context->VSSetConstantBuffers(start, num, &buffer);
	}
	void PSSetConstantBuffers(unsigned int start, unsigned int num, ID3D11Buffer* buffer)
	{
		_Context->PSSetConstantBuffers(start, num, &buffer);
	}
	void BindInputLayout(ID3D11InputLayout* input_layout)
	{
		_Context->IASetInputLayout(input_layout);
	}
	void Map(ID3D11Resource* resource, unsigned int subresource, D3D11_MAP map_type, unsigned int map_flags, D3D11_MAPPED_SUBRESOURCE* mapped_resources)
	{
		_Context->Map(resource, subresource, map_type, map_flags, mapped_resources);
	}
	void Unmap(ID3D11Resource* resource, unsigned int subresource)
	{
		_Context->Unmap(resource, subresource);
	}
	void DrawIndexed(unsigned int size, unsigned int start, unsigned int base)
	{
		_Context->DrawIndexed(size, start, base);
	}

	ID3D11Resource* CreateTexture2D(void* data, unsigned int size)
	{
		//D3DX11_IMAGE_INFO info;
		//D3DX11GetImageInfoFromMemory(data, size, nullptr, &info, nullptr);
		ID3D11Resource* resource = NULL;

		D3DX11_IMAGE_LOAD_INFO load_info;
		load_info.Width = 256;
		load_info.Height = 256;
		load_info.Depth = D3DX11_DEFAULT;
		load_info.FirstMipLevel = 0;
		load_info.MipLevels = 8;
		load_info.Usage = D3D11_USAGE_DEFAULT;
		load_info.CpuAccessFlags = D3D11_CPU_ACCESS_READ | D3D11_CPU_ACCESS_WRITE;
		load_info.MiscFlags = 0;
		load_info.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		load_info.Filter = D3DX11_FILTER_LINEAR;
		load_info.MipFilter = D3DX11_FILTER_LINEAR;
		load_info.pSrcInfo = nullptr;
		D3DX11CreateTextureFromMemory(_Device, data, size, &load_info, nullptr, &resource, nullptr);

		return resource;
	}

	ID3D11ShaderResourceView* CreateShaderResourceView(ID3D11Resource* resource)
	{
		D3D11_SHADER_RESOURCE_VIEW_DESC desc;
		desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		desc.ViewDimension = D3D_SRV_DIMENSION_TEXTURE2D;
		desc.Texture2D.MostDetailedMip = 0;
		desc.Texture2D.MipLevels = -1;

		ID3D11ShaderResourceView* shader_resource_view;
		_Device->CreateShaderResourceView(resource, &desc, &shader_resource_view);

		return shader_resource_view;
	}

	void PSSetShaderResource(unsigned int start, unsigned int num, ID3D11ShaderResourceView* resource_view)
	{
		_Context->PSSetShaderResources(start, num, &resource_view);
	}

	void PSSetSamplers(void)
	{
		_Context->PSSetSamplers(0, 1, &_SamplerState);
	}

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