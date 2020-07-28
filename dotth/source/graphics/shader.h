
#pragma once

#include "Framework/Base.h"
#include "graphics/renderer.h"

class sdr2222 : public Base
{
private:
	struct MatrixBufferType
	{
		XMMATRIX world;
		XMMATRIX view;
		XMMATRIX projection;
	};

public:
	bool Initialize(ID3D11Device*, HWND a = 0);
	void Shutdown();
	bool Render(ID3D11DeviceContext*, int, XMMATRIX*, XMMATRIX*, XMMATRIX*);

private:
	bool InitializeShader(ID3D11Device*, HWND, WCHAR*, WCHAR*);
	void ShutdownShader();
	void OutputShaderErrorMessage(ID3D10Blob*, HWND, WCHAR*);

	bool SetShaderParameters(ID3D11DeviceContext*, XMMATRIX*, XMMATRIX*, XMMATRIX*);
	void RenderShader(ID3D11DeviceContext*, int);

private:
	ID3D11VertexShader* m_vertexShader = nullptr;
	ID3D11PixelShader* m_pixelShader = nullptr;
	ID3D11InputLayout* m_layout = nullptr;
	ID3D11Buffer* m_matrixBuffer = nullptr;
};



class shader : public Base
{
private:
	const char* _vertex_shader_target = "vs_5_0";
	const char* _pixel_shader_target = "ps_5_0";

protected:
	ID3D11VertexShader* _vertex_shader = nullptr;
	ID3D11PixelShader* _pixel_shader = nullptr;
	ID3D11InputLayout* _layout = nullptr;
	ID3D11Buffer* _matrix_buffer = nullptr;

public:
	bool load(const wchar_t* FilePath, const char* EntryPoint = "main")
	{
		std::wstring file_path = FilePath;
		ID3D10Blob* error_message = nullptr;		

		std::wstring vs = file_path + L".vs";		
		ID3D10Blob* vertex_shader_buffer = nullptr;
		if (FAILED(D3DCompileFromFile(vs.c_str(), nullptr, nullptr, EntryPoint, _vertex_shader_target, D3D10_SHADER_ENABLE_STRICTNESS, 0, &vertex_shader_buffer, &error_message)))
			return false;

		std::wstring ps = file_path + L".ps";
		ID3D10Blob* pixel_shader_buffer = nullptr;
		if (FAILED(D3DCompileFromFile(ps.c_str(), nullptr, nullptr, EntryPoint, _pixel_shader_target, D3D10_SHADER_ENABLE_STRICTNESS, 0, &pixel_shader_buffer, &error_message)))
			return false;

		if (FAILED(renderer::device()->CreateVertexShader(vertex_shader_buffer->GetBufferPointer(), vertex_shader_buffer->GetBufferSize(), NULL, &_vertex_shader)))
			return false;

		if (FAILED(renderer::device()->CreatePixelShader(pixel_shader_buffer->GetBufferPointer(), pixel_shader_buffer->GetBufferSize(), NULL, &_pixel_shader)))
			return false;

		std::vector<D3D11_INPUT_ELEMENT_DESC> vertex_info_list = get_input_layout();
		if (FAILED(renderer::device()->CreateInputLayout(vertex_info_list.data(), static_cast<unsigned int>(vertex_info_list.size()), vertex_shader_buffer->GetBufferPointer(), vertex_shader_buffer->GetBufferSize(), &_layout)))
			return false;

		D3D11_BUFFER_DESC matrix_buffer_desc = get_matrix_buffer_desc();
		if (FAILED(renderer::device()->CreateBuffer(&matrix_buffer_desc, NULL, &_matrix_buffer)))
			return false;

		vertex_shader_buffer->Release();
		vertex_shader_buffer = nullptr;
		pixel_shader_buffer->Release();
		pixel_shader_buffer = nullptr;

		return true;
	}

	bool reset(void)
	{
		pre_reset();
		if (_vertex_shader)
		{
			_vertex_shader->Release();
			_vertex_shader = nullptr;
		}
		if (_pixel_shader)
		{
			_pixel_shader->Release();
			_pixel_shader = nullptr;
		}
		if (_layout)
		{
			_layout->Release();
			_layout = nullptr;
		}
		if (_matrix_buffer)
		{ 
			_matrix_buffer->Release();
			_matrix_buffer = nullptr;
		}
		post_reset();
	}

protected:
	virtual std::vector<D3D11_INPUT_ELEMENT_DESC> get_input_layout(void) = 0;
	virtual D3D11_BUFFER_DESC get_matrix_buffer_desc(void) = 0;
	virtual void pre_reset(void) {}
	virtual void post_reset(void) {}
};