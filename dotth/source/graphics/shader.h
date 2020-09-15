
#pragma once

#include "Graphics/Renderer.h"

namespace shader {
	enum stage : unsigned {
		begin, vs = 0, ps, end
	};

	union blobs {
		struct
		{
			ID3D10Blob* vs;
			ID3D10Blob* ps;
		};
		ID3D10Blob* of[shader::stage::end] = { nullptr };
	};
	union reflections {
		struct
		{
			ID3D11ShaderReflection* vs;
			ID3D11ShaderReflection* ps;
		};
		ID3D11ShaderReflection* of[shader::stage::end] = { nullptr };
	};

	union layouts {
		struct layout {
			std::vector<D3D11_SHADER_TYPE_DESC> types;
			unsigned int size;
			unsigned int slot;
		};
	};
}

using namespace shader;
class Shader : public Base
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

			void** buffer = reinterpret_cast<void**>(&_Reflections.of[desc._Stage]);
			GUID k = {};
			k.Data1 = 0x8d536ca1;
			k.Data2 = 0x0cca;
			k.Data3 = 0x4956;
			k.Data4[0] = 0xa8;
			k.Data4[1] = 0x37;
			k.Data4[2] = 0x78;
			k.Data4[3] = 0x69;
			k.Data4[4] = 0x63;
			k.Data4[5] = 0x75;
			k.Data4[6] = 0x55;
			k.Data4[7] = 0x84;
			// 0x8d536ca1, 0x0cca, 0x4956, 0xa8, 0x37, 0x78, 0x69, 0x63, 0x75, 0x55, 0x84
			D3DReflect(_Blobs.of[desc._Stage]->GetBufferPointer(), _Blobs.of[desc._Stage]->GetBufferSize(), k, reinterpret_cast<void**>(&_Reflections.of[desc._Stage]));

			D3D11_SHADER_DESC sd;
			_Reflections.of[desc._Stage]->GetDesc(&sd);

			unsigned bufSlot = 0;
			for (unsigned i = 0; i < sd.ConstantBuffers; ++i)
			{
				D3D11_SHADER_BUFFER_DESC					__desc;
				std::vector<D3D11_SHADER_VARIABLE_DESC>		__variables;
				std::vector<D3D11_SHADER_TYPE_DESC>			__types;

				ID3D11ShaderReflectionConstantBuffer* pCBuffer = _Reflections.of[desc._Stage]->GetConstantBufferByIndex(i);
				pCBuffer->GetDesc(&__desc);

				unsigned int buff_size = 0;
				// load desc of each variable for binding on buffer later on
				for (unsigned j = 0; j < __desc.Variables; ++j)
				{
					// get variable and type descriptions
					ID3D11ShaderReflectionVariable* pVariable = pCBuffer->GetVariableByIndex(j);
					D3D11_SHADER_VARIABLE_DESC varDesc;
					pVariable->GetDesc(&varDesc);
					__variables.push_back(varDesc);

					ID3D11ShaderReflectionType* pType = pVariable->GetType();
					D3D11_SHADER_TYPE_DESC typeDesc;
					pType->GetDesc(&typeDesc);
					__types.push_back(typeDesc);

					// accumulate buffer size
					buff_size += varDesc.Size;
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

