#include "Graphics/RHI/D11/D11RHI.h"
#include "Graphics/RHI/D11/D11Resource.h"
#include "Graphics/Camera.h"

bool D11RHI::Init(void* handle, int width, int height)
{ 
	D3D_FEATURE_LEVEL feature_levels[] =
	{
		D3D_FEATURE_LEVEL_11_1,
		//D3D_FEATURE_LEVEL_11_0,
	};
	
	if (FAILED(D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE::D3D_DRIVER_TYPE_HARDWARE, nullptr, 0, feature_levels, sizeof(feature_levels) / sizeof(D3D_FEATURE_LEVEL), D3D11_SDK_VERSION, &_Device, nullptr, &_Context)))
		return false;

	IDXGIFactory* factory = nullptr;
	if (FAILED(CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&factory)))
		return false;
	
	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.BufferCount = 1;
	sd.BufferDesc.Width = width;
	sd.BufferDesc.Height = height;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = (HWND)handle;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.Windowed = true;
	if (FAILED(factory->CreateSwapChain(_Device, &sd, &_SwapChain)))
		return false;
	
	ID3D11Texture2D* back_buffer_ptr = nullptr;
	if (FAILED(_SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&back_buffer_ptr))))
		return false;
	if (FAILED(_Device->CreateRenderTargetView(back_buffer_ptr, NULL, &_RenderTargetView)))
		return false;
	back_buffer_ptr->Release();

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
	ID3D11Texture2D* depth_stencil_buffer = nullptr;
	if (FAILED(_Device->CreateTexture2D(&depth_buffer_desc, NULL, &depth_stencil_buffer)))
		return false;
	
	D3D11_DEPTH_STENCIL_VIEW_DESC depth_stencil_view_desc;
	ZeroMemory(&depth_stencil_view_desc, sizeof(depth_stencil_view_desc));
	depth_stencil_view_desc.Format = depth_buffer_desc.Format;
	depth_stencil_view_desc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	depth_stencil_view_desc.Texture2D.MipSlice = 0;
	if (FAILED(_Device->CreateDepthStencilView(depth_stencil_buffer, &depth_stencil_view_desc, &_DepthBuffer)))
		return false;
	depth_stencil_buffer->Release();

	_Context->OMSetRenderTargets(1, &_RenderTargetView, _DepthBuffer);
	
	D3D11_VIEWPORT viewport;
	viewport.Width = static_cast<float>(width);
	viewport.Height = static_cast<float>(height);
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	viewport.TopLeftX = 0.0f;
	viewport.TopLeftY = 0.0f;

	_Context->RSSetViewports(1, &viewport);

	Camera::Instance()->SetViewportSize(width, height);

	return true;
}

void D11RHI::PreDraw(void)
{
	_Context->ClearRenderTargetView(_RenderTargetView, DirectX::Colors::MidnightBlue);
	_Context->ClearDepthStencilView(_DepthBuffer, D3D11_CLEAR_DEPTH, 1.0f, 0);
}

void D11RHI::PostDraw(void)
{
	_SwapChain->Present(0, 0);
}

bool D11RHI::Release(void)
{
	_Device->Release();
	_Context->Release();
	_SwapChain->Release();
	_RenderTargetView->Release();
	_DepthBuffer->Release();
	return false;
}

VertexBufferRHI * D11RHI::CreateVertexBuffer(unsigned int size, unsigned int usage, IDataSize * resource_info)
{
	D3D11_BUFFER_DESC desc;
	ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.ByteWidth = size;
	desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	desc.CPUAccessFlags = 0;
	desc.MiscFlags = 0;
	desc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA data;
	data.pSysMem = resource_info->GetData();
	data.SysMemPitch = 0;
	data.SysMemSlicePitch = 0;

	ID3D11Buffer* buffer = nullptr;
	if (FAILED(_Device->CreateBuffer(&desc, &data, &buffer)))
		return nullptr;
	return new D11VertexBuffer(buffer, size, usage);
}

IndexBufferRHI * D11RHI::CreateIndexBuffer(unsigned int size, unsigned int usage, IDataSize* resource_info)
{
	// 정적 인덱스 버퍼의 구조체를 설정합니다.
	D3D11_BUFFER_DESC desc;
	ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.ByteWidth = size;
	desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	desc.CPUAccessFlags = 0;
	desc.MiscFlags = 0;
	desc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA data;
	data.pSysMem = resource_info->GetData();
	data.SysMemPitch = 0;
	data.SysMemSlicePitch = 0;

	ID3D11Buffer* buffer = nullptr;
	if (FAILED(_Device->CreateBuffer(&desc, &data, &buffer)))
		return nullptr;
	return new D11IndexBuffer(buffer, size, usage);
}

void D11RHI::BindVertexBuffer(VertexBufferRHI * buffer, unsigned int stride, unsigned int offset)
{
	auto vertex_buffer = buffer->GetResource<ID3D11Buffer>();
	_Context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	_Context->IASetVertexBuffers(0, 1, &vertex_buffer, &stride, &offset);
}

void D11RHI::BindIndexBuffer(IndexBufferRHI * buffer, unsigned int format, unsigned int offset)
{
	auto index_buffer = buffer->GetResource<ID3D11Buffer>();
	_Context->IASetIndexBuffer(index_buffer, static_cast<DXGI_FORMAT>(format), offset);
}

VertexShaderRHI * D11RHI::CreateVertexShader(std::string file_path, void* vertex_desc, unsigned int num_desc)
{
	ID3D10Blob* error_message = nullptr;
	ID3D10Blob* shader_buffer = nullptr;
	ID3D11VertexShader* shader = nullptr;
	if (CompileShaderFromFile(&shader_buffer, file_path, "vs_5_0"))
	{
		_Device->CreateVertexShader(shader_buffer->GetBufferPointer(), shader_buffer->GetBufferSize(), NULL, &shader);
		ID3D11InputLayout* layout = nullptr;
		_Device->CreateInputLayout(static_cast<D3D11_INPUT_ELEMENT_DESC*>(vertex_desc), num_desc, shader_buffer->GetBufferPointer(), shader_buffer->GetBufferSize(), &layout);
		shader_buffer->Release();
		return new D11VertexShader(shader, layout);
	}
	return nullptr;
}

PixelShaderRHI * D11RHI::CreatePixelShader(std::string file_path)
{
	ID3D10Blob* error_message = nullptr;
	ID3D10Blob* shader_buffer = nullptr;
	ID3D11PixelShader* shader = nullptr;
	if (CompileShaderFromFile(&shader_buffer, file_path, "ps_5_0"))
	{
		_Device->CreatePixelShader(shader_buffer->GetBufferPointer(), shader_buffer->GetBufferSize(), NULL, &shader);
		shader_buffer->Release();
		return new D11PixelShader(shader);
	}
	return nullptr;
}

void D11RHI::PSSetResources(unsigned int start, unsigned int num, void * buffer)
{
	ID3D11ShaderResourceView* casted_buffer = static_cast<ID3D11ShaderResourceView*>(buffer);
	_Context->PSSetShaderResources(start, num, &casted_buffer);
}

void D11RHI::PSSetSamplers(unsigned int start, unsigned int num, void * buffer) 
{
	ID3D11SamplerState* casted_buffer = static_cast<ID3D11SamplerState*>(buffer);
	_Context->PSSetSamplers(start, num, &casted_buffer);
}

void D11RHI::BindVertexShader(VertexShaderRHI * shader) 
{
	ID3D11VertexShader* vertex_shader = shader->GetResource<ID3D11VertexShader>();
	_Context->VSSetShader(vertex_shader, nullptr, 0);
}

void D11RHI::BindPixelShader(PixelShaderRHI * shader) 
{
	ID3D11PixelShader* pixel_shader = shader->GetResource<ID3D11PixelShader>();
	_Context->PSSetShader(pixel_shader, nullptr, 0);
}

void D11RHI::UpdateSubreousrce(BufferRHI * buffer, void * data)
{
	_Context->UpdateSubresource(buffer->GetResource<ID3D11Buffer>(), 0, nullptr, data, 0, 0);
}

void D11RHI::DrawIndexed(unsigned int size, unsigned int start, unsigned int base)
{
	_Context->DrawIndexed(size, start, base);
}

void D11RHI::SetInputLayout(VertexShaderRHI * vertex_shader)
{
	D11VertexShader* shader = static_cast<D11VertexShader*>(vertex_shader);
	_Context->IASetInputLayout(shader->Layout);
}

bool D11RHI::CompileShaderFromFile(ID3DBlob** out, std::string file_path, std::string model, std::string entry)
{
	std::wstring w_file_path(file_path.begin(), file_path.end());	
	ID3D10Blob* error_message = nullptr;
	D3DCompileFromFile(w_file_path.c_str(), NULL, NULL, entry.c_str(), model.c_str(), D3D10_SHADER_ENABLE_STRICTNESS, 0, out, &error_message);
	return true;
}
