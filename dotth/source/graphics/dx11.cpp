#include "graphics/dx11.h"

bool dx11::initialize(HWND hwnd, int width, int height, bool vsync)
{
	IDXGIFactory* factory = nullptr;
	if (FAILED(CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&factory)))
	{
		return false;
	}

	IDXGIAdapter* adapter = nullptr;
	if (FAILED(factory->EnumAdapters(0, &adapter)))
	{
		return false;
	}

	IDXGIOutput* adapter_output = nullptr;
	if (FAILED(adapter->EnumOutputs(0, &adapter_output)))
	{
		return false;
	}

	unsigned int num_modes = 0;
	if (FAILED(adapter_output->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &num_modes, NULL)))
	{
		return false;
	}

	if (num_modes <= 0)
	{
		return false;
	}

	DXGI_MODE_DESC* display_model_list = new DXGI_MODE_DESC[num_modes];

	if (FAILED(adapter_output->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &num_modes, display_model_list)))
	{
		return false;
	}

	unsigned int numerator = 0;
	unsigned int denominator = 0;
	for (unsigned int i = 0; i < num_modes; i++)
	{
		if (display_model_list[i].Width == (unsigned int)width)
		{
			if (display_model_list[i].Height == (unsigned int)height)
			{
				numerator = display_model_list[i].RefreshRate.Numerator;
				denominator = display_model_list[i].RefreshRate.Denominator;
			}
		}
	}

	DXGI_ADAPTER_DESC adapter_desc;
	if (FAILED(adapter->GetDesc(&adapter_desc)))
	{
		return false;
	}

	_vga_memory_size = (int)(adapter_desc.DedicatedVideoMemory / 1024 / 1024);

	size_t stringLength = 0;
	if (wcstombs_s(&stringLength, _vga_desc, 128, adapter_desc.Description, 128) != 0)
	{
		return false;
	}

	delete[] display_model_list;
	display_model_list = nullptr;

	adapter_output->Release();
	adapter_output = nullptr;

	adapter->Release();
	adapter = nullptr;

	factory->Release();
	factory = nullptr;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	DXGI_SWAP_CHAIN_DESC swap_chain_desc;
	ZeroMemory(&swap_chain_desc, sizeof(swap_chain_desc));
	swap_chain_desc.BufferCount = 1;
	swap_chain_desc.BufferDesc.Width = width;
	swap_chain_desc.BufferDesc.Height = height;
	swap_chain_desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swap_chain_desc.BufferDesc.RefreshRate.Numerator = _vsync_enabled ? numerator : 0;
	swap_chain_desc.BufferDesc.RefreshRate.Denominator = _vsync_enabled ? denominator : 1;
	swap_chain_desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swap_chain_desc.OutputWindow = hwnd;
	swap_chain_desc.SampleDesc.Count = 1;
	swap_chain_desc.SampleDesc.Quality = 0;
	swap_chain_desc.Windowed = true;
	swap_chain_desc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swap_chain_desc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	swap_chain_desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	swap_chain_desc.Flags = 0;

	D3D_FEATURE_LEVEL feature_level = D3D_FEATURE_LEVEL_11_1;
	if (FAILED(D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, 0, &feature_level, 1, D3D11_SDK_VERSION, &swap_chain_desc, &_swap_chain, &_device, NULL, &_device_context)))
	{
		return false;
	}

	ID3D11Texture2D* back_buffer_ptr = nullptr;
	if (FAILED(_swap_chain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&back_buffer_ptr)))
	{
		return false;
	}

	if (FAILED(_device->CreateRenderTargetView(back_buffer_ptr, NULL, &_render_target_view)))
	{
		return false;
	}

	back_buffer_ptr->Release();
	back_buffer_ptr = 0;

	D3D11_TEXTURE2D_DESC depth_buffer_desc;
	ZeroMemory(&depth_buffer_desc, sizeof(depth_buffer_desc));
	depth_buffer_desc.Width = width;
	depth_buffer_desc.Height = height;
	depth_buffer_desc.MipLevels = 1;
	depth_buffer_desc.ArraySize = 1;
	depth_buffer_desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depth_buffer_desc.SampleDesc.Count = 1;
	depth_buffer_desc.SampleDesc.Quality = 0;
	depth_buffer_desc.Usage = D3D11_USAGE_DEFAULT;
	depth_buffer_desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depth_buffer_desc.CPUAccessFlags = 0;
	depth_buffer_desc.MiscFlags = 0;

	if (FAILED(_device->CreateTexture2D(&depth_buffer_desc, NULL, &_depth_stencil_buffer)))
	{
		return false;
	}

	D3D11_DEPTH_STENCIL_DESC depth_stencil_desc;
	ZeroMemory(&depth_stencil_desc, sizeof(depth_stencil_desc));
	depth_stencil_desc.DepthEnable = true;
	depth_stencil_desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depth_stencil_desc.DepthFunc = D3D11_COMPARISON_LESS;
	depth_stencil_desc.StencilEnable = true;
	depth_stencil_desc.StencilReadMask = 0xFF;
	depth_stencil_desc.StencilWriteMask = 0xFF;
	depth_stencil_desc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depth_stencil_desc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	depth_stencil_desc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depth_stencil_desc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
	depth_stencil_desc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depth_stencil_desc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
	depth_stencil_desc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depth_stencil_desc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	if (FAILED(_device->CreateDepthStencilState(&depth_stencil_desc, &_depth_stencil_state)))
	{
		return false;
	}

	_device_context->OMSetDepthStencilState(_depth_stencil_state, 1);

	D3D11_DEPTH_STENCIL_VIEW_DESC depth_stencil_view_desc;
	ZeroMemory(&depth_stencil_view_desc, sizeof(depth_stencil_view_desc));
	depth_stencil_view_desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depth_stencil_view_desc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	depth_stencil_view_desc.Texture2D.MipSlice = 0;
	if (FAILED(_device->CreateDepthStencilView(_depth_stencil_buffer, &depth_stencil_view_desc, &_depth_stencil_view)))
	{
		return false;
	}

	_device_context->OMSetRenderTargets(1, &_render_target_view, _depth_stencil_view);

	D3D11_RASTERIZER_DESC raster_desc;
	raster_desc.AntialiasedLineEnable = false;
	raster_desc.CullMode = D3D11_CULL_BACK;
	raster_desc.DepthBias = 0;
	raster_desc.DepthBiasClamp = 0.0f;
	raster_desc.DepthClipEnable = true;
	raster_desc.FillMode = D3D11_FILL_SOLID;
	raster_desc.FrontCounterClockwise = false;
	raster_desc.MultisampleEnable = false;
	raster_desc.ScissorEnable = false;
	raster_desc.SlopeScaledDepthBias = 0.0f;
	if (FAILED(_device->CreateRasterizerState(&raster_desc, &_raster_state)))
	{
		return false;
	}
	_device_context->RSSetState(_raster_state);

	D3D11_VIEWPORT viewport;
	viewport.Width = (float)width;
	viewport.Height = (float)height;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	viewport.TopLeftX = 0.0f;
	viewport.TopLeftY = 0.0f;

	_device_context->RSSetViewports(1, &viewport);

	float fieldOfView = XM_PI / 4.0f;
	float screenAspect = (float)width / (float)height;
	float camera_near = 1.f;
	float camera_far = 100000.f;
	_perspective_matrix = XMMatrixPerspectiveFovLH(fieldOfView, screenAspect, camera_near, camera_far);
	_ortho_matrix = XMMatrixOrthographicLH((float)width, (float)height, camera_near, camera_far);

	D3D11_BLEND_DESC blend_state_desc;
	ZeroMemory(&blend_state_desc, sizeof(D3D11_BLEND_DESC));
	blend_state_desc.RenderTarget[0].BlendEnable = TRUE;
	blend_state_desc.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
	blend_state_desc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
	blend_state_desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	blend_state_desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	blend_state_desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	blend_state_desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	blend_state_desc.RenderTarget[0].RenderTargetWriteMask = 0x0f;
	if (FAILED(_device->CreateBlendState(&blend_state_desc, &_alpha_enable_blending_state)))
	{
		return false;
	}
	blend_state_desc.RenderTarget[0].BlendEnable = FALSE;
	if (FAILED(_device->CreateBlendState(&blend_state_desc, &_alpha_disabl_blending_state)))
	{
		return false;
	}

	
	return true;
}

bool dx11::draw_begin(void)
{
	float color[4] = { 0.f, 0.f, 1.f, 1.f };

	// 백버퍼를 지웁니다
	_device_context->ClearRenderTargetView(_render_target_view, color);

	// 깊이 버퍼를 지웁니다
	_device_context->ClearDepthStencilView(_depth_stencil_view, D3D11_CLEAR_DEPTH, 1.0f, 0);

	return false;
}

bool dx11::draw_end(void)
{
	_swap_chain->Present(_vsync_enabled? 1 : 0, 0);

	return false;
}

bool dx11::release(void)
{
	_device->Release();
	_device_context->Release();
	_swap_chain->Release();
	_render_target_view->Release();
	_depth_stencil_buffer->Release();
	_depth_stencil_state->Release();
	_depth_stencil_view->Release();
	_raster_state->Release();
	_alpha_enable_blending_state->Release();
	_alpha_disabl_blending_state->Release();
	return false;
}
