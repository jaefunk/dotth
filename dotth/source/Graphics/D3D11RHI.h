
#pragma once

#include "DynamicRHI.h"

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")
#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>

using namespace DirectX;

class D3D11RHI : public DynamicRHI
{
public:
	bool initialize(HWND hwnd, int width, int height);
	bool draw_begin(void);
	bool draw_end(void);
	bool release(void);

public:
	ID3D11Device* device(void) {
		return _device;
	}
	ID3D11DeviceContext* context(void) {
		return _device_context;
	}

private:
	ID3D11Device* _device = nullptr;
	ID3D11DeviceContext* _device_context = nullptr;
	IDXGISwapChain* _swap_chain = nullptr;
	ID3D11RenderTargetView* _render_target_view = nullptr;
	ID3D11Texture2D* _depth_stencil_buffer = nullptr;
	ID3D11DepthStencilState* _depth_stencil_state = nullptr;
	ID3D11DepthStencilView* _depth_stencil_view = nullptr;
	ID3D11RasterizerState* _raster_state = nullptr;
	ID3D11BlendState* _alpha_enable_blending_state = nullptr;
	ID3D11BlendState* _alpha_disabl_blending_state = nullptr;

	int _vga_memory_size = 0;
	char _vga_desc[128] = { 0, };
};

// D3D11RHI