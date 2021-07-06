


#include "D3D11StaticMesh.h"

void D3D11StaticMesh::Load(const char * file)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(file, aiProcess_ConvertToLeftHanded | aiProcess_Triangulate | aiProcess_OptimizeMeshes);
	
	for (unsigned int index = 0; index < scene->mNumMeshes; ++index)
	{
		aiMesh* mesh = scene->mMeshes[index];
		if (mesh->HasFaces())
		{
			Vertices.resize(mesh->mNumVertices);
			for (unsigned int i = 0; i < mesh->mNumVertices; ++i)
			{
				Vertices[i].Position.x = mesh->mVertices[i].x;
				Vertices[i].Position.y = mesh->mVertices[i].y;
				Vertices[i].Position.z = mesh->mVertices[i].z;
				Vertices[i].Color = { 
					static_cast<float>((rand() & 256)) / 256.f, 
					static_cast<float>((rand() & 256)) / 256.f, 
					static_cast<float>((rand() & 256)) / 256.f, 
					1.f };

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
			for (unsigned int i = 0; i < mesh->mNumFaces; ++i)
			{
				const aiFace& face = mesh->mFaces[i];
				unsigned int current = i * 3U;
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
		memset(&data, 0, sizeof(decltype(data)));
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
		memset(&data, 0, sizeof(decltype(data)));
		data.pSysMem = Indices.data();
		data.SysMemPitch = 0;
		data.SysMemSlicePitch = 0;
		D3D11RHI::Device()->CreateBuffer(&desc, &data, &_IndexBuffer);
	}
}

void D3D11StaticMesh::Draw(void)
{
	const unsigned int offset = 0;
	const unsigned int vertex_type_size = static_cast<unsigned int>(sizeof(decltype(Vertices)::value_type));
	D3D11RHI::Context()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	D3D11RHI::Context()->IASetVertexBuffers(0, 1, &_VertexBuffer, &vertex_type_size, &offset);
	D3D11RHI::Context()->IASetIndexBuffer(_IndexBuffer, DXGI_FORMAT_R32_UINT, 0);
}