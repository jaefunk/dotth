
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
	virtual VertexBufferRHI* CreateVertexBuffer(unsigned int size, unsigned int usage, IDataSize* resource_info) override;
	virtual IndexBufferRHI* CreateIndexBuffer(unsigned int size, unsigned int usage, IDataSize* resource_info) override;
	virtual void BindVertexBuffer(VertexBufferRHI* buffer, unsigned int stride, unsigned int offset) override;
	virtual void BindIndexBuffer(IndexBufferRHI* buffer, unsigned int format, unsigned int offset) override;

	virtual VertexShaderRHI* CreateVertexShader(void) override;
	virtual PixelShaderRHI* CreatePixelShader(void) override;
	

private:
	ID3D11Device* _Device = nullptr;
	ID3D11DeviceContext* _Context = nullptr;
	IDXGISwapChain* _SwapChain = nullptr;
	ID3D11RenderTargetView* _RenderTargetView = nullptr;
	ID3D11DepthStencilView* _DepthBuffer = nullptr;
};

// D11RHI