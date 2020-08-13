
#pragma once

#include "dotth.h"

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")
#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include <directxcolors.h>

#include "Graphics/RHI/ResourceRHI.h"

using namespace DirectX;
class D11RHI
{
public:
	bool Init(void* handle, int width, int height);
	void PreDraw(void);
	void PostDraw(void);
	bool Release(void);

public:
	ID3D11Device* Device(void) {
		return _Device;
	}
	ID3D11DeviceContext* Context(void) {
		return _Context; 
	}

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

	VertexBufferRHI* CreateVertexBuffer(unsigned int size, unsigned int usage, IDataSize* resource_info);

	
	ConstantBufferRHI* CreateConstantBuffer(unsigned int size)
	{
		ID3D11Buffer* constant_buffer = nullptr;
		D3D11_BUFFER_DESC desc;
		desc.Usage = D3D11_USAGE_DYNAMIC;
		desc.ByteWidth = size;
		desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		desc.MiscFlags = 0;
		desc.StructureByteStride = 0;
		_Device->CreateBuffer(&desc, NULL, &constant_buffer);
		return new ConstantBufferRHI(constant_buffer, size);
	}

	
	IndexBufferRHI* CreateIndexBuffer(unsigned int size, unsigned int usage, IDataSize* resource_info);
	void BindVertexBuffer(VertexBufferRHI* buffer, unsigned int stride, unsigned int offset);
	void BindIndexBuffer(IndexBufferRHI* buffer, unsigned int format, unsigned int offset);

	VertexShaderRHI* CreateVertexShader(std::string file_path, void* vertex_desc, unsigned int num_desc);
	PixelShaderRHI* CreatePixelShader(std::string file_path);

	
	void PSSetResources(unsigned int start, unsigned int num, void* buffer);
	void PSSetSamplers(unsigned int start, unsigned int num, void* buffer);

	void BindVertexShader(VertexShaderRHI* shader);
	void BindPixelShader(PixelShaderRHI* shader);

	void UpdateSubreousrce(BufferRHI* buffer, void* data);

	void DrawIndexed(unsigned int size, unsigned int start, unsigned int base);

	void SetInputLayout(VertexShaderRHI* vertex_shader);


private:
	ID3D11Device* _Device = nullptr;
	ID3D11DeviceContext* _Context = nullptr;
	IDXGISwapChain* _SwapChain = nullptr;
	ID3D11RenderTargetView* _RenderTargetView = nullptr;
	ID3D11DepthStencilView* _DepthBuffer = nullptr;

public:
	static bool CompileShaderFromFile(ID3DBlob** out, std::string file_path, std::string model, std::string entry = "main");
};

// D11RHI