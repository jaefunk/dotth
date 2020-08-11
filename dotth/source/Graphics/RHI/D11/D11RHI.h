
#pragma once

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")
#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include <directxcolors.h>

#include "Graphics/RHI/DynamicRHI.h"
#include "Graphics/RHI/ResourceRHI.h"

using namespace DirectX;
class D11RHI : public DynamicRHI
{
public:
	virtual bool Init(void* handle, int width, int height) override;
	virtual void PreDraw(void) override;
	virtual void PostDraw(void) override;
	bool Release(void);

public:
	//ID3D11Device* device(void) {
	//	return _Device;
	//}
	//ID3D11DeviceContext* context(void) {
	//	return _Context;
	//}
	virtual void* GetNativeDevice(void) 
	{
		return _Device;
	};
	virtual void* GetNativeContext(void) 
	{
		return _Context;
	};

	virtual ConstantBufferRHI* CreateConstantBuffer(unsigned int size) override
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

	virtual VertexBufferRHI* CreateVertexBuffer(unsigned int size, unsigned int usage, IDataSize* resource_info) override;
	virtual IndexBufferRHI* CreateIndexBuffer(unsigned int size, unsigned int usage, IDataSize* resource_info) override;
	virtual void BindVertexBuffer(VertexBufferRHI* buffer, unsigned int stride, unsigned int offset) override;
	virtual void BindIndexBuffer(IndexBufferRHI* buffer, unsigned int format, unsigned int offset) override;

	virtual VertexShaderRHI* CreateVertexShader(std::string file_path, void* vertex_desc, unsigned int num_desc) override;
	virtual PixelShaderRHI* CreatePixelShader(std::string file_path) override;

	virtual void VSSetConstantBuffers(unsigned int start, unsigned int num, void* buffer) override;
	virtual void PSSetConstantBuffers(unsigned int start, unsigned int num, void* buffer) override;
	virtual void PSSetResources(unsigned int start, unsigned int num, void* buffer) override;
	virtual void PSSetSamplers(unsigned int start, unsigned int num, void* buffer) override;
	
	virtual void BindVertexShader(VertexShaderRHI* shader) override;
	virtual void BindPixelShader(PixelShaderRHI* shader) override;

	virtual void UpdateSubreousrce(BufferRHI* buffer, void* data) override;

	virtual void DrawIndexed(unsigned int size, unsigned int start, unsigned int base) override;

	virtual void SetInputLayout(VertexShaderRHI* vertex_shader) override;


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