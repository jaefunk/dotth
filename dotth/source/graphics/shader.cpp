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

		if (reflection == nullptr)
			continue;

		D3D11_SHADER_DESC shader_desc;
		reflection->GetDesc(&shader_desc);

		std::vector<D3D11_INPUT_ELEMENT_DESC> elements;
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

			elements.push_back(desc);
		}

		_InputLayout = Renderer::RHI()->CreateInputLayout(_Blobs.of[desc.stage], elements.data(), elements.size());

		for (unsigned slot = 0; slot < shader_desc.ConstantBuffers; ++slot)
		{
			layout l;
			l.slot = slot;
			if (ID3D11ShaderReflectionConstantBuffer* reflection_constant_buffer = reflection->GetConstantBufferByIndex(l.slot))
			{
				reflection_constant_buffer->GetDesc(&l.desc);
				for (unsigned int index = 0; index < l.desc.Variables; ++index)
				{
					if (ID3D11ShaderReflectionVariable* reflection_variable = reflection_constant_buffer->GetVariableByIndex(index))
					{
						D3D11_SHADER_VARIABLE_DESC variable_desc;
						reflection_variable->GetDesc(&variable_desc);
						l.variables.push_back(variable_desc);

						if (ID3D11ShaderReflectionType* reflection_type = reflection_variable->GetType())
						{
							D3D11_SHADER_TYPE_DESC type_desc;
							reflection_type->GetDesc(&type_desc);
							l.types.push_back(type_desc);
						}
					}
				}
			}
			_Layouts.push_back(l);
		}

		for (auto layout : _Layouts)
		{
			for (auto variable : layout.variables)
			{
				cpu_buffer cb;
				cb.name = variable.Name;
				cb.size = variable.Size;
				cb.data = new char[variable.Size];
				memset(cb.data, 0, cb.size);
				_CBuffers.push_back(cb);
			}

			D3D11_BUFFER_DESC buffer_desc;
			buffer_desc.Usage = D3D11_USAGE_DYNAMIC;
			buffer_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
			buffer_desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
			buffer_desc.MiscFlags = 0;
			buffer_desc.StructureByteStride = 0;
			buffer_desc.ByteWidth = layout.desc.Size;

			gpu_buffer gb;
			gb.buffer = Renderer::RHI()->CreateConstantBuffer(buffer_desc);
			gb.dirty = true;
			gb.stage = desc.stage;
			gb.slot = layout.slot;
			_GBuffers.push_back(gb);
		}

		for (unsigned int index = 0; index < shader_desc.BoundResources; ++index)
		{
			D3D11_SHADER_INPUT_BIND_DESC input_bind_desc;
			reflection->GetResourceBindingDesc(index, &input_bind_desc);

			switch (input_bind_desc.Type)
			{
			case D3D_SIT_SAMPLER:
			{
			} break;

			case D3D_SIT_TEXTURE:
			{
			} break;

			case D3D_SIT_UAV_RWTYPED:
			{
			} break;

			case D3D_SIT_CBUFFER: break;
			default:
				break;

			}
		}
		
		_Blobs.of[desc.stage]->Release();
	}
	//	for (unsigned slot = 0; slot < shader_desc.ConstantBuffers; ++slot)
	//	{
	//		_Layouts2.of[desc.stage] = new layout;
	//		_Layouts2.of[desc.stage]->slot = slot;

	//		ID3D11ShaderReflectionConstantBuffer* pCBuffer = reflection->GetConstantBufferByIndex(slot);
	//		pCBuffer->GetDesc(&_Layouts2.of[desc.stage]->desc);

	//		unsigned int buff_size = 0;
	//		for (unsigned index = 0; index < _Layouts2.of[desc.stage]->desc.Variables; ++index)
	//		{
	//			ID3D11ShaderReflectionVariable* pVariable = pCBuffer->GetVariableByIndex(index);
	//			D3D11_SHADER_VARIABLE_DESC varDesc;
	//			pVariable->GetDesc(&varDesc);

	//			ID3D11ShaderReflectionType* pType = pVariable->GetType();
	//			D3D11_SHADER_TYPE_DESC typeDesc;
	//			pType->GetDesc(&typeDesc);

	//			_Layouts2.of[desc.stage]->variables.push_back(varDesc);
	//			_Layouts2.of[desc.stage]->types.push_back(typeDesc);
	//			_Layouts2.of[desc.stage]->size += varDesc.Size;
	//		}
	//	}

	//	for (unsigned int index = 0; index < _Layouts2.of[desc.stage]->variables.size(); ++index)
	//	{
	//		auto variable = _Layouts2.of[desc.stage]->variables[index];
	//		cpu_buffer cb;
	//		cb.name = variable.Name;
	//		cb.size = variable.Size;
	//		cb.data = new char[variable.Size];
	//		memset(cb.data, 0, cb.size);
	//		_CpuBuffers.push_back(cb);
	//	}


	//	D3D11_BUFFER_DESC buffer_desc;
	//	buffer_desc.Usage = D3D11_USAGE_DYNAMIC;
	//	buffer_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	//	buffer_desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	//	buffer_desc.MiscFlags = 0;
	//	buffer_desc.StructureByteStride = 0;
	//	buffer_desc.ByteWidth = _Layouts2.of[desc.stage]->desc.Size;

	//	gpu_buffer gb;
	//	gb.slot = _Layouts2.of[desc.stage]->slot;
	//	gb.dirty = true;
	//	gb.buffer = Renderer::RHI()->CreateConstantBuffer(buffer_desc);
	//}
}
