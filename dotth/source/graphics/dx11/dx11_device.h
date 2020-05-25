
#pragma once

#include "dx11.h"

class dx11_device
{
public:
	bool initialize(HWND hwnd, int width, int height, bool vsync = false);
	bool draw_begin(void);
	bool draw_end(void);
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
	XMMATRIX _perspective_matrix;
	XMMATRIX _ortho_matrix;
	
	HWND _hwnd;
	int _width = 0;
	int _height = 0;	
	bool _vsync_enabled = false;
	int _vga_memory_size = 0;
	char _vga_desc[128] = { 0, };
	
};