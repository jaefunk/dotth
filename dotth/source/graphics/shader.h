
#pragma once

#include "Graphics/Renderer.h"

namespace shader {
	enum stage : unsigned {
		begin, vs = 0, ps, end
	};

	union blobs {
		struct {
			ID3D10Blob* vs;
			ID3D10Blob* ps;
		};
		ID3D10Blob* of[shader::stage::end] = { nullptr };
	};
	union reflections {
		struct {
			ID3D11ShaderReflection* vs;
			ID3D11ShaderReflection* ps;
		};
		ID3D11ShaderReflection* of[shader::stage::end] = { nullptr };
	};

	struct layout {
		D3D11_SHADER_BUFFER_DESC desc;
		std::vector<D3D11_SHADER_VARIABLE_DESC> variables;
		std::vector<D3D11_SHADER_TYPE_DESC> types;
		unsigned int size = 0;
		unsigned int slot = 0;
	};

	union layouts {
		struct {
			layout* vs;
			layout* ps;
		};
		layout* of[shader::stage::end] = { nullptr };
	};
}

using namespace shader;
class Shader
{	
private:
	struct COMPILE_DESC {
		stage _Stage;
		const char* _CompilerVersion;
		const char* _EntryPoint;
	};
	const std::vector<COMPILE_DESC> _ShaderDesc = {
		{stage::vs, "vs_5_0", "vs_main"},
		{stage::ps, "ps_5_0", "ps_main"},
	};

private:
	blobs _Blobs;
	reflections _Reflections;
	layouts _Layouts;

	ID3D11VertexShader* _VertexShader = nullptr;
	ID3D11PixelShader* _PixelShader = nullptr;
	ID3D11InputLayout* _InputLayout = nullptr;

public:
	void LoadShader(std::string fp)
	{
		std::wstring wfp(fp.begin(), fp.end());
		ID3D10Blob* error_message = nullptr;
		for (auto const& desc : _ShaderDesc)
		{
			_Blobs.of[desc._Stage] = nullptr;
			D3DCompileFromFile(wfp.c_str(), nullptr, nullptr, desc._EntryPoint, desc._CompilerVersion, D3DCOMPILE_ENABLE_STRICTNESS, 0, &_Blobs.of[desc._Stage], &error_message);
			if (error_message)
			{
				std::string err = Utility::Str::Format("%s / %s", fp.c_str(), error_message->GetBufferPointer());
				OutputDebugStringA(err.c_str());
				error_message->Release();
			}

			if (_Blobs.of[desc._Stage] == nullptr)
				continue;

			switch (desc._Stage)
			{
			case shader::stage::vs: 
				_VertexShader = Renderer::RHI()->CreateVertexShader(_Blobs.of[desc._Stage]);
				break;
			case shader::stage::ps:
				_PixelShader = Renderer::RHI()->CreatePixelShader(_Blobs.of[desc._Stage]);
				break;
			default:
				break;
			}

			auto reflection = _Reflections.of[desc._Stage];
			GUID guid = { 0x8d536ca1, 0x0cca, 0x4956, { 0xa8, 0x37, 0x78, 0x69, 0x63, 0x75, 0x55, 0x84 } };
			D3DReflect(_Blobs.of[desc._Stage]->GetBufferPointer(), _Blobs.of[desc._Stage]->GetBufferSize(), guid, reinterpret_cast<void**>(&reflection));		
			
			D3D11_SHADER_DESC shader_desc;
			reflection->GetDesc(&shader_desc);

			unsigned int buff_slot = 0;
			for (unsigned buff_slot = 0; buff_slot < shader_desc.ConstantBuffers; ++buff_slot)
			{
				_Layouts.of[desc._Stage] = new layout;
				_Layouts.of[desc._Stage]->slot = buff_slot;
				
				ID3D11ShaderReflectionConstantBuffer* pCBuffer = reflection->GetConstantBufferByIndex(buff_slot);
				pCBuffer->GetDesc(&_Layouts.of[desc._Stage]->desc);

				unsigned int buff_size = 0;
				for (unsigned index = 0; index < _Layouts.of[desc._Stage]->desc.Variables; ++index)
				{
					ID3D11ShaderReflectionVariable* pVariable = pCBuffer->GetVariableByIndex(index);
					D3D11_SHADER_VARIABLE_DESC varDesc;
					pVariable->GetDesc(&varDesc);
					_Layouts.of[desc._Stage]->variables.push_back(varDesc);

					ID3D11ShaderReflectionType* pType = pVariable->GetType();
					D3D11_SHADER_TYPE_DESC typeDesc;
					pType->GetDesc(&typeDesc);
					_Layouts.of[desc._Stage]->types.push_back(typeDesc);

					_Layouts.of[desc._Stage]->size += varDesc.Size;
				}
				
			}
		}
	}

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

