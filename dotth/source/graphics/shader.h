
#pragma once

#include "Graphics/Renderer.h"

namespace shader {
	enum ESTAGE : unsigned int {
		BEGIN, VS = 0, PS, END
	};

	struct compile_desc {
		ESTAGE stage;
		const char* version;
		const char* entrypoint;
	};

	struct layout {
		D3D11_SHADER_BUFFER_DESC desc;
		std::vector<D3D11_SHADER_VARIABLE_DESC> variables;
		std::vector<D3D11_SHADER_TYPE_DESC> types;
		unsigned int size = 0;
		unsigned int slot = 0;
	};

	union blobs {
		struct {
			ID3D10Blob* vs;
			ID3D10Blob* ps;
		};
		ID3D10Blob* of[ESTAGE::END] = { nullptr };
	};

	union reflections {
		struct {
			ID3D11ShaderReflection* vs;
			ID3D11ShaderReflection* ps;
		};
		ID3D11ShaderReflection* of[ESTAGE::END] = { nullptr };
	};

	union layouts {
		struct {
			layout* vs;
			layout* ps;
		};
		layout* of[ESTAGE::END] = { nullptr };
	};

	
	//struct gpu_buffer {

	//};
}

using namespace shader;
class Shader
{	
private:
	const std::vector<compile_desc> _CompileDesc = {
		{ ESTAGE::VS, "vs_5_0", "vs_main" },
		{ ESTAGE::PS, "ps_5_0", "ps_main" },
	};

private:
	blobs _Blobs;
	reflections _Reflections;
	layouts _Layouts;

	ID3D11InputLayout* _InputLayout = nullptr;
	ID3D11VertexShader* _VertexShader = nullptr;
	ID3D11PixelShader* _PixelShader = nullptr;
	

public:
	void LoadShader(std::string fp);
};

class Shader2
{
protected:
	ID3D11VertexShader* _VertexShader = nullptr;
	ID3D11PixelShader* _PixelShader = nullptr;
	ID3D11InputLayout* _InputLayout = nullptr;
public:
	bool LoadShader(std::string file_name, D3D11_INPUT_ELEMENT_DESC* input_desc = nullptr, unsigned int desc_size = 0)
	{
		std::wstring w_file_name(file_name.begin(), file_name.end());
		ID3D10Blob* error_message = nullptr;

		ID3D10Blob* vs_out = nullptr;
		D3DCompileFromFile(w_file_name.c_str(), nullptr, nullptr, "vs_main", "vs_5_0", D3DCOMPILE_ENABLE_STRICTNESS, 0, &vs_out, &error_message);
		if (error_message)
		{
			OutputDebugStringA((char*)error_message->GetBufferPointer());
			error_message->Release();
		}
		_VertexShader = Renderer::RHI()->CreateVertexShader(vs_out);
		if (input_desc != nullptr && desc_size != 0)
			_InputLayout = Renderer::RHI()->CreateInputLayout(vs_out, input_desc, desc_size);
		vs_out->Release();

		ID3D10Blob* ps_out = nullptr;
		D3DCompileFromFile(w_file_name.c_str(), nullptr, nullptr, "ps_main", "ps_5_0", D3DCOMPILE_ENABLE_STRICTNESS, 0, &ps_out, &error_message);
		_PixelShader = Renderer::RHI()->CreatePixelShader(ps_out);
		ps_out->Release();
		return true;
	}
	void Draw(ID3D11Buffer* buffer, unsigned int size)
	{
		Renderer::RHI()->VSSetConstantBuffers(0, 1, buffer);
		Renderer::RHI()->BindInputLayout(_InputLayout);
		Renderer::RHI()->VSSetShader(_VertexShader);
		Renderer::RHI()->PSSetShader(_PixelShader);
		Renderer::RHI()->DrawIndexed(size, 0, 0);
	}
};

