#include "Shader.h"

void Shader::LoadShader(std::string fp)
{
	std::wstring wfp(fp.begin(), fp.end());
	ID3D10Blob* error_message = nullptr;
	for (auto const& desc : _CompileDesc)
	{
		_Blobs.of[desc.stage] = nullptr;
		D3DCompileFromFile(wfp.c_str(), nullptr, nullptr, desc.entrypoint, desc.version, D3DCOMPILE_ENABLE_STRICTNESS, 0, &_Blobs.of[desc.stage], &error_message);
		if (error_message)
		{
			std::string err = Utility::Str::Format("%s / %s", fp.c_str(), error_message->GetBufferPointer());
			OutputDebugStringA(err.c_str());
			error_message->Release();
		}

		if (_Blobs.of[desc.stage] == nullptr)
			continue;

		switch (desc.stage)
		{
		case ESTAGE::VS:
			_VertexShader = Renderer::RHI()->CreateVertexShader(_Blobs.of[desc.stage]);
			break;
		case ESTAGE::PS:
			_PixelShader = Renderer::RHI()->CreatePixelShader(_Blobs.of[desc.stage]);
			break;
		default:
			break;
		}

		ID3D11ShaderReflection* reflection = _Reflections.of[desc.stage];
		GUID guid = { 0x8d536ca1, 0x0cca, 0x4956,{ 0xa8, 0x37, 0x78, 0x69, 0x63, 0x75, 0x55, 0x84 } };
		D3DReflect(_Blobs.of[desc.stage]->GetBufferPointer(), _Blobs.of[desc.stage]->GetBufferSize(), guid, reinterpret_cast<void**>(&reflection));

		D3D11_SHADER_DESC shader_desc;
		reflection->GetDesc(&shader_desc);
		
		std::vector<D3D11_INPUT_ELEMENT_DESC> elements;
		elements.resize(shader_desc.InputParameters);
		for (unsigned int index = 0; index < shader_desc.InputParameters; ++index)
		{
			D3D11_SIGNATURE_PARAMETER_DESC signature;
			reflection->GetInputParameterDesc(index, &signature);

			D3D11_INPUT_ELEMENT_DESC desc;
			desc.SemanticName = signature.SemanticName;
			desc.SemanticIndex = signature.SemanticIndex;
			desc.InputSlot = 0;
			desc.AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
			desc.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
			desc.InstanceDataStepRate = 0;

			if (signature.Mask == 1 && signature.ComponentType == D3D_REGISTER_COMPONENT_UINT32)
				desc.Format = DXGI_FORMAT_R32_UINT;
			else if (signature.Mask == 1 && signature.ComponentType == D3D_REGISTER_COMPONENT_SINT32)
				desc.Format = DXGI_FORMAT_R32_SINT;
			else if (signature.Mask == 1 && signature.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32)
				desc.Format = DXGI_FORMAT_R32_FLOAT;
			else if (signature.Mask <= 3 && signature.ComponentType == D3D_REGISTER_COMPONENT_UINT32)
				desc.Format = DXGI_FORMAT_R32G32_UINT;
			else if (signature.Mask <= 3 && signature.ComponentType == D3D_REGISTER_COMPONENT_SINT32)
				desc.Format = DXGI_FORMAT_R32G32_SINT;
			else if (signature.Mask <= 3 && signature.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32)
				desc.Format = DXGI_FORMAT_R32G32_FLOAT;
			else if (signature.Mask <= 7 && signature.ComponentType == D3D_REGISTER_COMPONENT_UINT32)
				desc.Format = DXGI_FORMAT_R32G32B32_UINT;
			else if (signature.Mask <= 7 && signature.ComponentType == D3D_REGISTER_COMPONENT_SINT32)
				desc.Format = DXGI_FORMAT_R32G32B32_SINT;
			else if (signature.Mask <= 7 && signature.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32)
				desc.Format = DXGI_FORMAT_R32G32B32_FLOAT;
			else if (signature.Mask <= 15 && signature.ComponentType == D3D_REGISTER_COMPONENT_UINT32)
				desc.Format = DXGI_FORMAT_R32G32B32A32_UINT;
			else if (signature.Mask <= 15 && signature.ComponentType == D3D_REGISTER_COMPONENT_SINT32)
				desc.Format = DXGI_FORMAT_R32G32B32A32_SINT;
			else if (signature.Mask <= 15 && signature.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32)
				desc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;

			elements[index] = desc;
		}

		_InputLayout = Renderer::RHI()->CreateInputLayout(_Blobs.of[desc.stage], elements.data(), elements.size());

		for (unsigned buff_slot = 0; buff_slot < shader_desc.ConstantBuffers; ++buff_slot)
		{
			_Layouts.of[desc.stage] = new layout;
			_Layouts.of[desc.stage]->slot = buff_slot;

			ID3D11ShaderReflectionConstantBuffer* pCBuffer = reflection->GetConstantBufferByIndex(buff_slot);
			pCBuffer->GetDesc(&_Layouts.of[desc.stage]->desc);

			unsigned int buff_size = 0;
			for (unsigned index = 0; index < _Layouts.of[desc.stage]->desc.Variables; ++index)
			{
				ID3D11ShaderReflectionVariable* pVariable = pCBuffer->GetVariableByIndex(index);
				D3D11_SHADER_VARIABLE_DESC varDesc;
				pVariable->GetDesc(&varDesc);

				ID3D11ShaderReflectionType* pType = pVariable->GetType();
				D3D11_SHADER_TYPE_DESC typeDesc;
				pType->GetDesc(&typeDesc);

				_Layouts.of[desc.stage]->variables.push_back(varDesc);
				_Layouts.of[desc.stage]->types.push_back(typeDesc);
				_Layouts.of[desc.stage]->size += varDesc.Size;
			}
		}


	}
}
