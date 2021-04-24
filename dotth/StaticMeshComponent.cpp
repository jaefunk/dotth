#include "StaticMeshComponent.h"

void StaticMeshComponent::OnInit(void)
{
	_Camera.SetViewportSize(640, 480);
	_Camera.SetAt(DirectX::XMFLOAT3(0.f, 0.f, 0.f));
	_Camera.SetUp(DirectX::XMFLOAT3(0.f, 1.f, 0.f));
	_Camera.SetEye(DirectX::XMFLOAT3(0.f, 9.f, -9.f));
	_Camera.SetFieldOfView(DirectX::XM_PI * 0.25f);
	_Camera.SetNear(0.1f);
	_Camera.SetFar(1000.f);

	_StaticMesh.Vertices.resize(24);
	_StaticMesh.Vertices[0]  = Vertex(Vector3F(-1.0f, +1.0f, -1.0f), Color4F(1.0f, 0.0f, 0.f, 1.f));
	_StaticMesh.Vertices[1]  = Vertex(Vector3F(+1.0f, +1.0f, -1.0f), Color4F(1.0f, 0.0f, 0.f, 1.f));
	_StaticMesh.Vertices[2]  = Vertex(Vector3F(+1.0f, +1.0f, +1.0f), Color4F(1.0f, 0.0f, 0.f, 1.f));
	_StaticMesh.Vertices[3]  = Vertex(Vector3F(-1.0f, +1.0f, +1.0f), Color4F(1.0f, 0.0f, 0.f, 1.f));
	_StaticMesh.Vertices[4]  = Vertex(Vector3F(-1.0f, -1.0f, -1.0f), Color4F(0.0f, 1.0f, 0.f, 1.f));
	_StaticMesh.Vertices[5]  = Vertex(Vector3F(+1.0f, -1.0f, -1.0f), Color4F(0.0f, 1.0f, 0.f, 1.f));
	_StaticMesh.Vertices[6]  = Vertex(Vector3F(+1.0f, -1.0f, +1.0f), Color4F(0.0f, 1.0f, 0.f, 1.f));
	_StaticMesh.Vertices[7]  = Vertex(Vector3F(-1.0f, -1.0f, +1.0f), Color4F(0.0f, 1.0f, 0.f, 1.f));
	_StaticMesh.Vertices[8]  = Vertex(Vector3F(-1.0f, -1.0f, +1.0f), Color4F(0.0f, 0.0f, 1.f, 1.f));
	_StaticMesh.Vertices[9]  = Vertex(Vector3F(-1.0f, -1.0f, -1.0f), Color4F(0.0f, 0.0f, 1.f, 1.f));
	_StaticMesh.Vertices[10] = Vertex(Vector3F(-1.0f, +1.0f, -1.0f), Color4F(0.0f, 0.0f, 1.f, 1.f));
	_StaticMesh.Vertices[11] = Vertex(Vector3F(-1.0f, +1.0f, +1.0f), Color4F(0.0f, 0.0f, 1.f, 1.f));
	_StaticMesh.Vertices[12] = Vertex(Vector3F(+1.0f, -1.0f, +1.0f), Color4F(1.0f, 0.0f, 1.f, 1.f));
	_StaticMesh.Vertices[13] = Vertex(Vector3F(+1.0f, -1.0f, -1.0f), Color4F(1.0f, 0.0f, 1.f, 1.f));
	_StaticMesh.Vertices[14] = Vertex(Vector3F(+1.0f, +1.0f, -1.0f), Color4F(1.0f, 0.0f, 1.f, 1.f));
	_StaticMesh.Vertices[15] = Vertex(Vector3F(+1.0f, +1.0f, +1.0f), Color4F(1.0f, 0.0f, 1.f, 1.f));
	_StaticMesh.Vertices[16] = Vertex(Vector3F(-1.0f, -1.0f, -1.0f), Color4F(0.0f, 1.0f, 1.f, 1.f));
	_StaticMesh.Vertices[17] = Vertex(Vector3F(+1.0f, -1.0f, -1.0f), Color4F(0.0f, 1.0f, 1.f, 1.f));
	_StaticMesh.Vertices[18] = Vertex(Vector3F(+1.0f, +1.0f, -1.0f), Color4F(0.0f, 1.0f, 1.f, 1.f));
	_StaticMesh.Vertices[19] = Vertex(Vector3F(-1.0f, +1.0f, -1.0f), Color4F(0.0f, 1.0f, 1.f, 1.f));
	_StaticMesh.Vertices[20] = Vertex(Vector3F(-1.0f, -1.0f, +1.0f), Color4F(1.0f, 1.0f, 0.f, 1.f));
	_StaticMesh.Vertices[21] = Vertex(Vector3F(+1.0f, -1.0f, +1.0f), Color4F(1.0f, 1.0f, 0.f, 1.f));
	_StaticMesh.Vertices[22] = Vertex(Vector3F(+1.0f, +1.0f, +1.0f), Color4F(1.0f, 1.0f, 0.f, 1.f));
	_StaticMesh.Vertices[23] = Vertex(Vector3F(-1.0f, +1.0f, +1.0f), Color4F(1.0f, 1.0f, 0.f, 1.f));

	_StaticMesh.Indices.resize(36);
	_StaticMesh.Indices[0] = 3;
	_StaticMesh.Indices[1] = 1;
	_StaticMesh.Indices[2] = 0;
	_StaticMesh.Indices[3] = 2;
	_StaticMesh.Indices[4] = 1;
	_StaticMesh.Indices[5] = 3;
	_StaticMesh.Indices[6] = 6;
	_StaticMesh.Indices[7] = 4;
	_StaticMesh.Indices[8] = 5;
	_StaticMesh.Indices[9] = 7;
	_StaticMesh.Indices[10] = 4;
	_StaticMesh.Indices[11] = 6;
	_StaticMesh.Indices[12] = 11;
	_StaticMesh.Indices[13] = 9;
	_StaticMesh.Indices[14] = 8;
	_StaticMesh.Indices[15] = 10;
	_StaticMesh.Indices[16] = 9;
	_StaticMesh.Indices[17] = 11;
	_StaticMesh.Indices[18] = 14;
	_StaticMesh.Indices[19] = 12;
	_StaticMesh.Indices[20] = 13;
	_StaticMesh.Indices[21] = 15;
	_StaticMesh.Indices[22] = 12;
	_StaticMesh.Indices[23] = 14;
	_StaticMesh.Indices[24] = 19;
	_StaticMesh.Indices[25] = 17;
	_StaticMesh.Indices[26] = 16;
	_StaticMesh.Indices[27] = 18;
	_StaticMesh.Indices[28] = 17;
	_StaticMesh.Indices[29] = 19;
	_StaticMesh.Indices[30] = 22;
	_StaticMesh.Indices[31] = 20;
	_StaticMesh.Indices[32] = 21;
	_StaticMesh.Indices[33] = 23;
	_StaticMesh.Indices[34] = 20;
	_StaticMesh.Indices[35] = 22;


	const unsigned int vertex_type_size = static_cast<unsigned int>(sizeof(decltype(_StaticMesh.Vertices)::value_type));
	const unsigned int index_type_size = static_cast<unsigned int>(sizeof(decltype(_StaticMesh.Indices)::value_type));

	{
		D3D11_BUFFER_DESC desc;
		memset(&desc, 0, sizeof(decltype(desc)));
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.ByteWidth = vertex_type_size * static_cast<unsigned int>(_StaticMesh.Vertices.size());
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	
		D3D11_SUBRESOURCE_DATA data;
		memset(&data, 0, sizeof(decltype(data)));
		data.pSysMem = _StaticMesh.Vertices.data();
		data.SysMemPitch = 0;
		data.SysMemSlicePitch = 0;
		_VertexBuffer = D3D11RHI::CreateBuffer(&desc, &data);
	}

	{
		D3D11_BUFFER_DESC desc;
		memset(&desc, 0, sizeof(decltype(desc)));
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.ByteWidth = index_type_size * static_cast<unsigned int>(_StaticMesh.Indices.size());
		desc.BindFlags = D3D11_BIND_INDEX_BUFFER;

		D3D11_SUBRESOURCE_DATA data;
		memset(&data, 0, sizeof(decltype(data)));
		data.pSysMem = _StaticMesh.Indices.data();
		data.SysMemPitch = 0;
		data.SysMemSlicePitch = 0;
		_IndexBuffer = D3D11RHI::CreateBuffer(&desc, &data);
	}
	
	{
		unsigned int size;
		D3D11_INPUT_ELEMENT_DESC* layout = new D3D11_INPUT_ELEMENT_DESC[2];
		layout[0] = { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 };
		layout[1] = { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 };
		size = 2;
		LoadShader("Resource/Primitive.hlsl", layout, size);
	}
	
	{
		D3D11_BUFFER_DESC desc;
		memset(&desc, 0, sizeof(decltype(desc)));
		desc.ByteWidth = sizeof(MatrixBuffer);
		desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		desc.Usage = D3D11_USAGE_DEFAULT;
		//desc.Usage = D3D11_USAGE_DYNAMIC;
		//desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		_ConstantBuffer = D3D11RHI::CreateBuffer(&desc, nullptr);
	}
}

void StaticMeshComponent::OnUpdate(void)
{
	_Camera.Sync();
}

void StaticMeshComponent::OnDraw(void)
{
	unsigned int offset;
	const unsigned int vertex_type_size = static_cast<unsigned int>(sizeof(decltype(_StaticMesh.Vertices)::value_type));
	D3D11RHI::Context()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	D3D11RHI::BindVertexBuffer(_VertexBuffer, vertex_type_size);
	D3D11RHI::BindIndexBuffer(_IndexBuffer);

	static float fX = 0.f;
	static float fY = 0.f;

	MatrixBuffer cb;
	cb.View = DirectX::XMMatrixTranspose(*_Camera.View());
	cb.Projection = DirectX::XMMatrixTranspose(*_Camera.Perspective());
	auto world = DirectX::XMMatrixRotationY(fX);
	world = world * DirectX::XMMatrixRotationZ(fY);

	fX += 0.0005f;
	fY += 0.001f;
	cb.World = DirectX::XMMatrixTranspose(world);
	D3D11RHI::Context()->UpdateSubresource(_ConstantBuffer, 0, nullptr,  &cb, 0, 0);

	//D3D11_MAPPED_SUBRESOURCE mapped_resource;
	//Renderer::RHI()->Map(_ConstantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped_resource);
	//MatrixBufferType* mbt = (MatrixBufferType*)mapped_resource.pData;
	//mbt->view = DirectX::XMMatrixTranspose(*Camera::Instance()->View());
	//mbt->projection = DirectX::XMMatrixTranspose(*Camera::Instance()->Perspective());
	//auto world = XMMatrixIdentity();
	//mbt->world = DirectX::XMMatrixTranspose(world);
	//Renderer::RHI()->Unmap(_ConstantBuffer, 0);

	//_Shader2.Draw(_ConstantBuffer, GetIndexCount());

	D3D11RHI::Context()->VSSetConstantBuffers(0, 1, &_ConstantBuffer);
	D3D11RHI::Context()->IASetInputLayout(_InputLayout);
	D3D11RHI::Context()->VSSetShader(_VertexShader, nullptr, 0);
	D3D11RHI::Context()->PSSetShader(_PixelShader, nullptr, 0);
	D3D11RHI::Context()->DrawIndexed(_StaticMesh.Indices.size(), 0, 0);
}

void StaticMeshComponent::OnDestroy(void)
{
}


bool StaticMeshComponent::LoadShader(std::string file_name, D3D11_INPUT_ELEMENT_DESC* input_desc, unsigned int desc_size)
{
	ID3D10Blob* error_message = nullptr;
	std::wstring w_file_name(file_name.begin(), file_name.end());

	std::ifstream file;
	file.open(file_name, std::ios_base::binary);
	
	std::string file_text;
	while (file) {
		std::string s;
		getline(file, s);
		file_text.append(s);
	}
	file.close();

	ID3D10Blob* vs_out = nullptr;
	
	D3DCompile(file_text.data(), file_text.length(), nullptr, nullptr, nullptr, "vs_main", "vs_5_0", 0, 0, &vs_out, &error_message);
	if (error_message)
	{
		OutputDebugStringA((char*)error_message->GetBufferPointer());
		error_message->Release();
		return false;
	}
	_VertexShader = D3D11RHI::CreateVertexShader(vs_out);
	if (input_desc != nullptr && desc_size != 0)
		_InputLayout = D3D11RHI::CreateInputLayout(vs_out, input_desc, desc_size);
	vs_out->Release();

	ID3D10Blob* ps_out = nullptr;
	D3DCompile(file_text.data(), file_text.length(), nullptr, nullptr, nullptr, "ps_main", "ps_5_0", 0, 0, &ps_out, &error_message);
	if (error_message)
	{
		OutputDebugStringA((char*)error_message->GetBufferPointer());
		error_message->Release();
		return false;
	}
	_PixelShader = D3D11RHI::CreatePixelShader(ps_out);
	ps_out->Release();
	return true;
}