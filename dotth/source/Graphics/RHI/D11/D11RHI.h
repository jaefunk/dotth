
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

	ID3D11Buffer* CreateVertexBuffer();

	ID3D11Buffer* CreateConstantBuffer(D3D11_BUFFER_DESC desc)
	{
		ID3D11Buffer* constant_buffer = nullptr;
		_Device->CreateBuffer(&desc, NULL, &constant_buffer);
		return constant_buffer;
	}
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

	VertexBufferRHI* CreateVertexBuffer(unsigned int size, unsigned int usage, IDataSize* resource_info);
	IndexBufferRHI* CreateIndexBuffer(unsigned int size, unsigned int usage, IDataSize* resource_info);
	void BindVertexBuffer(VertexBufferRHI* buffer, unsigned int stride, unsigned int offset);
	void BindIndexBuffer(IndexBufferRHI* buffer, unsigned int format, unsigned int offset);

	VertexShaderRHI* CreateVertexShader(std::string file_path, void* vertex_desc, unsigned int num_desc);
	PixelShaderRHI* CreatePixelShader(std::string file_path);

	void VSSetConstantBuffers(unsigned int start, unsigned int num, void* buffer);
	void PSSetConstantBuffers(unsigned int start, unsigned int num, void* buffer);
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