
#pragma once

#include "Components/DrawableComponent.h"
#include "Graphics/PrimitiveShader.h"
#include "Graphics/shader.h"

struct VertexType
{
	XMFLOAT3 position;
	XMFLOAT4 color;
};

struct MatrixBufferType
{
	XMMATRIX world;
	XMMATRIX view;
	XMMATRIX projection;
};

class PrimitiveComponent : public DrawableComponent
{
public:
	ID3D11Buffer* _ConstantBuffer = nullptr;
	PrimitiveShader* _Shader = nullptr;

public:
	virtual void OnInit(void) override
	{
		{
			int vertex_count = 3;

			VertexType vertices[3];
			vertices[0].position = XMFLOAT3(0.0f, 1.0f, 0.0f);
			vertices[0].color = XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);
			vertices[1].position = XMFLOAT3(1.0f, -1.0f, 0.0f);
			vertices[1].color = XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);
			vertices[2].position = XMFLOAT3(-1.0f, -1.0f, 0.0f);
			vertices[2].color = XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f);

			D3D11_BUFFER_DESC desc;
			memset(&desc, 0, sizeof(decltype(desc)));
			desc.Usage = D3D11_USAGE_DEFAULT;
			desc.ByteWidth = sizeof(VertexType) * vertex_count;
			desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

			D3D11_SUBRESOURCE_DATA data;
			memset(&data, 0, sizeof(decltype(data)));
			data.pSysMem = vertices;
			data.SysMemPitch = 0;
			data.SysMemSlicePitch = 0;

			_VertexBuffer = Renderer::RHI()->CreateVertexBuffer(desc, data);
		}

		{
			int index_count = 3;

			unsigned long indices[3];
			indices[0] = 0;
			indices[1] = 1;
			indices[2] = 2;

			D3D11_BUFFER_DESC desc;
			memset(&desc, 0, sizeof(decltype(desc)));
			desc.Usage = D3D11_USAGE_DEFAULT;
			desc.ByteWidth = sizeof(unsigned long) * index_count;
			desc.BindFlags = D3D11_BIND_INDEX_BUFFER;

			D3D11_SUBRESOURCE_DATA data;
			memset(&data, 0, sizeof(decltype(data)));
			data.pSysMem = indices;
			data.SysMemPitch = 0;
			data.SysMemSlicePitch = 0;
			_IndexBuffer = Renderer::RHI()->CreateIndexBuffer(desc, data);
		}

		{
			_Shader = new PrimitiveShader();
			D3D11_INPUT_ELEMENT_DESC layout[] =
			{
				{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
				{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			};
			unsigned int num_desc = sizeof(layout) / sizeof(layout[0]);
			_Shader->LoadShader("Resource/Primitive.fx", layout, 2);
		}

		{
			D3D11_BUFFER_DESC desc;
			memset(&desc, 0, sizeof(decltype(desc)));
			desc.ByteWidth = sizeof(MatrixBufferType);
			desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

			desc.Usage = D3D11_USAGE_DEFAULT;
			//desc.Usage = D3D11_USAGE_DYNAMIC;
			//desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

			_ConstantBuffer = Renderer::RHI()->CreateConstantBuffer(desc);
		}
	}

	virtual void OnUpdate(void) override
	{

	}

	virtual void OnDraw(void) override
	{
		Renderer::RHI()->BindVertexBuffer(_VertexBuffer, sizeof(VertexType), 0);
		Renderer::RHI()->BindIndexBuffer(_IndexBuffer, DXGI_FORMAT_R32_UINT, 0);
		
		MatrixBufferType cb;
		cb.view = DirectX::XMMatrixTranspose(*Camera::Instance()->View());
		cb.projection = DirectX::XMMatrixTranspose(*Camera::Instance()->Perspective());
		auto world = XMMatrixIdentity();
		cb.world = DirectX::XMMatrixTranspose(world);
		Renderer::RHI()->UpdateSubresource(_ConstantBuffer, &cb);

		//D3D11_MAPPED_SUBRESOURCE mapped_resource;
		//Renderer::RHI()->Map(_ConstantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped_resource);
		//MatrixBufferType* mbt = (MatrixBufferType*)mapped_resource.pData;
		//mbt->view = DirectX::XMMatrixTranspose(*Camera::Instance()->View());
		//mbt->projection = DirectX::XMMatrixTranspose(*Camera::Instance()->Perspective());
		//auto world = XMMatrixIdentity();
		//mbt->world = DirectX::XMMatrixTranspose(world);
		//Renderer::RHI()->Unmap(_ConstantBuffer, 0);

		_Shader->Draw(_ConstantBuffer);
	}
};

