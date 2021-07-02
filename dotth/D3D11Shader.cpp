
#include "D3D11Shader.h"

bool D3D11Shader::Load(const char * file_name)
{
	unsigned int desc_size = 2;
	D3D11_INPUT_ELEMENT_DESC* input_desc = new D3D11_INPUT_ELEMENT_DESC[desc_size];
	input_desc[0] = { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 };
	input_desc[1] = { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 };

	ID3DBlob* error_message = nullptr;

	std::ifstream file;
	file.open(file_name, std::ios_base::binary);

	std::string file_text;
	while (file) {
		std::string s;
		getline(file, s);
		file_text.append(s);
	}
	file.close();

	ID3DBlob* vs_out = nullptr;
	D3DCompile(file_text.data(), file_text.length(), nullptr, nullptr, nullptr, "vs_main", "vs_5_0", 0, 0, &vs_out, &error_message);

	if (error_message)
	{
		OutputDebugStringA((char*)error_message->GetBufferPointer());
		error_message->Release();
		return false;
	}

	D3D11RHI::Device()->CreateVertexShader(vs_out->GetBufferPointer(), vs_out->GetBufferSize(), nullptr, &_VertexShader);
	D3D11RHI::Device()->CreateInputLayout(input_desc, desc_size, vs_out->GetBufferPointer(), vs_out->GetBufferSize(), &_InputLayout);
	vs_out->Release();

	ID3DBlob* ps_out = nullptr;
	D3DCompile(file_text.data(), file_text.length(), nullptr, nullptr, nullptr, "ps_main", "ps_5_0", 0, 0, &ps_out, &error_message);
	if (error_message)
	{
		OutputDebugStringA((char*)error_message->GetBufferPointer());
		error_message->Release();
		return false;
	}

	D3D11RHI::Device()->CreatePixelShader(ps_out->GetBufferPointer(), ps_out->GetBufferSize(), nullptr, &_PixelShader);
	ps_out->Release();

	D3D11_BUFFER_DESC desc;
	memset(&desc, 0, sizeof(decltype(desc)));
	desc.ByteWidth = sizeof(XMMATRIX);
	desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	desc.Usage = D3D11_USAGE_DEFAULT;
	//desc.Usage = D3D11_USAGE_DYNAMIC;
	//desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	D3D11RHI::Device()->CreateBuffer(&desc, nullptr, &_ConstantBuffer);

	return true;
}

void D3D11Shader::Draw(const Matrix& matrix, unsigned int size)
{
	auto wv = XMMatrixMultiply(XMMatrixTranspose(D3D11RHI::Camera()->View()), matrix);
	auto result = XMMatrixMultiply(XMMatrixTranspose(D3D11RHI::Camera()->Perspective()), wv);
	D3D11RHI::Context()->UpdateSubresource(_ConstantBuffer, 0, nullptr, &result, 0, 0);
	D3D11RHI::Context()->VSSetConstantBuffers(0, 1, &_ConstantBuffer);
	D3D11RHI::Context()->IASetInputLayout(_InputLayout);
	D3D11RHI::Context()->VSSetShader(_VertexShader, nullptr, 0);
	D3D11RHI::Context()->PSSetShader(_PixelShader, nullptr, 0);
	D3D11RHI::Context()->DrawIndexed(size, 0, 0);
}
