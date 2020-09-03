#include "Shader.h"

bool Shader::LoadShader(std::string file_name, D3D11_INPUT_ELEMENT_DESC * input_desc, unsigned int desc_size)
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

void Shader::Draw(ID3D11Buffer * buffer, unsigned int size)
{
	Renderer::RHI()->VSSetConstantBuffers(0, 1, buffer);
	Renderer::RHI()->BindInputLayout(_InputLayout);
	Renderer::RHI()->VSSetShader(_VertexShader);
	Renderer::RHI()->PSSetShader(_PixelShader);
	Renderer::RHI()->DrawIndexed(size, 0, 0);

}
