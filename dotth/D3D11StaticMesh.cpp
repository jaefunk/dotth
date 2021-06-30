

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
#include "D3D11StaticMesh.h"

bool D3D11StaticMesh::LoadShader(std::string file_name)
{
	unsigned int desc_size = 2;
	D3D11_INPUT_ELEMENT_DESC* input_desc = new D3D11_INPUT_ELEMENT_DESC[desc_size];
	input_desc[0] = { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 };
	input_desc[1] = { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 };

	ID3DBlob* error_message = nullptr;
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

	

	ID3DBlob* vs_out = nullptr;
	//D3DCompileFromFile(L"a", nullptr, nullptr, "vs_main", "vs_5_0", 0, 0, &vs_out, &error_message);
	D3DCompile(file_text.data(), file_text.length(), nullptr, nullptr, nullptr, "vs_main", "vs_5_0", 0, 0, &vs_out, &error_message);
	//GUID guid;
	//guid.Data1 = 0xeb62d63d;
	//guid.Data2 = 0x93dd;
	//guid.Data3 = 0x4318;
	//guid.Data4[0] = 0x8a;
	//guid.Data4[1] = 0xe8;
	//guid.Data4[2] = 0xc6;
	//guid.Data4[3] = 0xf8;
	//guid.Data4[4] = 0x3a;
	//guid.Data4[5] = 0xd3;
	//guid.Data4[6] = 0x71;
	//guid.Data4[7] = 0xb8;
	//ID3D11ShaderReflectionConstantBuffer* cb;
	//D3DReflect(vs_out->GetBufferPointer(), vs_out->GetBufferSize(), guid, (void**)&cb);

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
	std::wstring wfp(file_name.begin(), file_name.end());
	//D3DCompileFromFile(wfp.c_str(), nullptr, nullptr, "ps_main", "ps_5_0", D3DCOMPILE_ENABLE_STRICTNESS, 0, &ps_out, &error_message);
	D3DCompile(file_text.data(), file_text.length(), nullptr, nullptr, nullptr, "ps_main", "ps_5_0", 0, 0, &ps_out, &error_message);
	if (error_message)
	{
		OutputDebugStringA((char*)error_message->GetBufferPointer());
		error_message->Release();
		return false;
	}
	
	D3D11RHI::Device()->CreatePixelShader(ps_out->GetBufferPointer(), ps_out->GetBufferSize(), nullptr, &_PixelShader);
	ps_out->Release();

	return true;
}

void D3D11StaticMesh::Load(const char * file)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(file, aiProcess_ConvertToLeftHanded | aiProcess_Triangulate | aiProcess_OptimizeMeshes);
	
	for (unsigned int index = 0; index < scene->mNumMeshes; ++index)
	{
		auto mesh = scene->mMeshes[index];
		if (mesh->HasFaces())
		{
			Vertices.resize(mesh->mNumVertices);
			for (unsigned int i = 0; i < mesh->mNumVertices; ++i)
			{
				Vertices[i].Position = { mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z };
				Vertices[i].Color = { static_cast<float>((rand()&256))/256.f, static_cast<float>((rand() & 256)) / 256.f, static_cast<float>((rand() & 256)) / 256.f, static_cast<float>((rand() & 256)) };

				const aiVector3D& n = mesh->mNormals[i];
				Vertices[i].Normal.x = n.x;
				Vertices[i].Normal.y = n.y;
				Vertices[i].Normal.z = n.z;

				if (mesh->HasTextureCoords(0))
				{
					const aiVector3D& u = mesh->mTextureCoords[0][i];
					Vertices[i].UV.x = u.x;
					Vertices[i].UV.y = u.y;
				}
			}
			Indices.resize(mesh->mNumFaces * 3);
			for (int i = 0; i < mesh->mNumFaces; ++i)
			{
				const aiFace& face = mesh->mFaces[i];
				unsigned int current = i * 3;
				Indices[current + 0] = face.mIndices[0];
				Indices[current + 1] = face.mIndices[1];
				Indices[current + 2] = face.mIndices[2];
			}
		}
	}

	//Vertices.resize(24);
	//Vertices[0] = Vertex(Vector3F(-0.5f, +0.5f, -0.5f), Color4F(1.0f, 0.0f, 0.f, 1.f));
	//Vertices[1] = Vertex(Vector3F(+0.5f, +0.5f, -0.5f), Color4F(1.0f, 0.0f, 0.f, 1.f));
	//Vertices[2] = Vertex(Vector3F(+0.5f, +0.5f, +0.5f), Color4F(1.0f, 0.0f, 0.f, 1.f));
	//Vertices[3] = Vertex(Vector3F(-0.5f, +0.5f, +0.5f), Color4F(1.0f, 0.0f, 0.f, 1.f));
	//Vertices[4] = Vertex(Vector3F(-0.5f, -0.5f, -0.5f), Color4F(0.0f, 1.0f, 0.f, 1.f));
	//Vertices[5] = Vertex(Vector3F(+0.5f, -0.5f, -0.5f), Color4F(0.0f, 1.0f, 0.f, 1.f));
	//Vertices[6] = Vertex(Vector3F(+0.5f, -0.5f, +0.5f), Color4F(0.0f, 1.0f, 0.f, 1.f));
	//Vertices[7] = Vertex(Vector3F(-0.5f, -0.5f, +0.5f), Color4F(0.0f, 1.0f, 0.f, 1.f));
	//Vertices[8] = Vertex(Vector3F(-0.5f, -0.5f, +0.5f), Color4F(0.0f, 0.0f, 1.f, 1.f));
	//Vertices[9] = Vertex(Vector3F(-0.5f, -0.5f, -0.5f), Color4F(0.0f, 0.0f, 1.f, 1.f));
	//Vertices[10] = Vertex(Vector3F(-0.5f, +0.5f, -0.5f), Color4F(0.0f, 0.0f, 1.f, 1.f));
	//Vertices[11] = Vertex(Vector3F(-0.5f, +0.5f, +0.5f), Color4F(0.0f, 0.0f, 1.f, 1.f));
	//Vertices[12] = Vertex(Vector3F(+0.5f, -0.5f, +0.5f), Color4F(1.0f, 0.0f, 1.f, 1.f));
	//Vertices[13] = Vertex(Vector3F(+0.5f, -0.5f, -0.5f), Color4F(1.0f, 0.0f, 1.f, 1.f));
	//Vertices[14] = Vertex(Vector3F(+0.5f, +0.5f, -0.5f), Color4F(1.0f, 0.0f, 1.f, 1.f));
	//Vertices[15] = Vertex(Vector3F(+0.5f, +0.5f, +0.5f), Color4F(1.0f, 0.0f, 1.f, 1.f));
	//Vertices[16] = Vertex(Vector3F(-0.5f, -0.5f, -0.5f), Color4F(0.0f, 1.0f, 1.f, 1.f));
	//Vertices[17] = Vertex(Vector3F(+0.5f, -0.5f, -0.5f), Color4F(0.0f, 1.0f, 1.f, 1.f));
	//Vertices[18] = Vertex(Vector3F(+0.5f, +0.5f, -0.5f), Color4F(0.0f, 1.0f, 1.f, 1.f));
	//Vertices[19] = Vertex(Vector3F(-0.5f, +0.5f, -0.5f), Color4F(0.0f, 1.0f, 1.f, 1.f));
	//Vertices[20] = Vertex(Vector3F(-0.5f, -0.5f, +0.5f), Color4F(1.0f, 1.0f, 0.f, 1.f));
	//Vertices[21] = Vertex(Vector3F(+0.5f, -0.5f, +0.5f), Color4F(1.0f, 1.0f, 0.f, 1.f));
	//Vertices[22] = Vertex(Vector3F(+0.5f, +0.5f, +0.5f), Color4F(1.0f, 1.0f, 0.f, 1.f));
	//Vertices[23] = Vertex(Vector3F(-0.5f, +0.5f, +0.5f), Color4F(1.0f, 1.0f, 0.f, 1.f));

	//Indices.resize(36);
	//Indices[0] = 3;
	//Indices[1] = 1;
	//Indices[2] = 0;
	//Indices[3] = 2;
	//Indices[4] = 1;
	//Indices[5] = 3;
	//Indices[6] = 6;
	//Indices[7] = 4;
	//Indices[8] = 5;
	//Indices[9] = 7;
	//Indices[10] = 4;
	//Indices[11] = 6;
	//Indices[12] = 11;
	//Indices[13] = 9;
	//Indices[14] = 8;
	//Indices[15] = 10;
	//Indices[16] = 9;
	//Indices[17] = 11;
	//Indices[18] = 14;
	//Indices[19] = 12;
	//Indices[20] = 13;
	//Indices[21] = 15;
	//Indices[22] = 12;
	//Indices[23] = 14;
	//Indices[24] = 19;
	//Indices[25] = 17;
	//Indices[26] = 16;
	//Indices[27] = 18;
	//Indices[28] = 17;
	//Indices[29] = 19;
	//Indices[30] = 22;
	//Indices[31] = 20;
	//Indices[32] = 21;
	//Indices[33] = 23;
	//Indices[34] = 20;
	//Indices[35] = 22;


	const unsigned int vertex_type_size = static_cast<unsigned int>(sizeof(decltype(Vertices)::value_type));
	const unsigned int index_type_size = static_cast<unsigned int>(sizeof(decltype(Indices)::value_type));

	{
		D3D11_BUFFER_DESC desc;
		memset(&desc, 0, sizeof(decltype(desc)));
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.ByteWidth = vertex_type_size * static_cast<unsigned int>(Vertices.size());
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

		D3D11_SUBRESOURCE_DATA data;
		//memset(&data, 0, sizeof(decltype(data)));
		data.pSysMem = Vertices.data();
		data.SysMemPitch = 0;
		data.SysMemSlicePitch = 0;
		D3D11RHI::Device()->CreateBuffer(&desc, &data, &_VertexBuffer);
	}

	{
		D3D11_BUFFER_DESC desc;
		memset(&desc, 0, sizeof(decltype(desc)));
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.ByteWidth = index_type_size * static_cast<unsigned int>(Indices.size());
		desc.BindFlags = D3D11_BIND_INDEX_BUFFER;

		D3D11_SUBRESOURCE_DATA data;
		//memset(&data, 0, sizeof(decltype(data)));
		data.pSysMem = Indices.data();
		data.SysMemPitch = 0;
		data.SysMemSlicePitch = 0;
		D3D11RHI::Device()->CreateBuffer(&desc, &data, &_IndexBuffer);
	}

	{
		D3D11_BUFFER_DESC desc;
		memset(&desc, 0, sizeof(decltype(desc)));
		desc.ByteWidth = sizeof(MatrixBuffer);
		desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		desc.Usage = D3D11_USAGE_DEFAULT;
		//desc.Usage = D3D11_USAGE_DYNAMIC;
		//desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		D3D11RHI::Device()->CreateBuffer(&desc, nullptr, &_ConstantBuffer);
	}

	{
		LoadShader("Resource/Primitive.hlsl");
	}
}

void D3D11StaticMesh::Draw(void)
{
	const unsigned int offset = 0;
	const unsigned int vertex_type_size = static_cast<unsigned int>(sizeof(decltype(Vertices)::value_type));

	MatrixBuffer cb;
	cb.View = DirectX::XMMatrixTranspose(D3D11RHI::Camera()->View());
	cb.Projection = DirectX::XMMatrixTranspose(D3D11RHI::Camera()->Perspective());
	cb.World = Matrix;
	D3D11RHI::Context()->UpdateSubresource(_ConstantBuffer, 0, nullptr, &cb, 0, 0);
	D3D11RHI::Context()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	D3D11RHI::Context()->IASetVertexBuffers(0, 1, &_VertexBuffer, &vertex_type_size, &offset);
	D3D11RHI::Context()->IASetIndexBuffer(_IndexBuffer, DXGI_FORMAT_R32_UINT, 0);
	D3D11RHI::Context()->VSSetConstantBuffers(0, 1, &_ConstantBuffer);
	D3D11RHI::Context()->IASetInputLayout(_InputLayout);
	D3D11RHI::Context()->VSSetShader(_VertexShader, nullptr, 0);
	D3D11RHI::Context()->PSSetShader(_PixelShader, nullptr, 0);
	D3D11RHI::Context()->DrawIndexed(static_cast<unsigned int>(Indices.size()), 0, 0);
}