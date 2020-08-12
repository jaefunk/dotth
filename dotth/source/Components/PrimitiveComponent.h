
#pragma once

#include "Components/DrawableComponent.h"
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

class PrimitiveComponent : public DrawableComponent<VertexType, int>
{
public:
	ConstantBufferRHI* ConstantBuffer = nullptr;
	ID3D11Buffer* _ConstantBuffer = nullptr;
	sdr2222 sd;

public:
	virtual void OnInit(void) override
	{
		sd.OnInit();

		{

		}

		{
			D3D11_BUFFER_DESC desc;
			memset(&desc, 0, sizeof(decltype(desc)));
			desc.Usage = D3D11_USAGE_DYNAMIC;
			desc.ByteWidth = sizeof(MatrixBufferType);
			desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
			desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
			desc.MiscFlags = 0;
			desc.StructureByteStride = 0;
			_ConstantBuffer = Renderer::RHI()->CreateConstantBuffer(desc);
		}

		int vertex_count = 3;
		VertexType vertices[3];
		vertices[0].position = XMFLOAT3(0.0f, 1.0f, 0.0f);
		vertices[0].color = XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);
		vertices[1].position = XMFLOAT3(1.0f, -1.0f, 0.0f);
		vertices[1].color = XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);
		vertices[2].position = XMFLOAT3(-1.0f, -1.0f, 0.0f);
		vertices[2].color = XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f);
		auto vertex_res = ResourceArray(vertices, vertex_count);
		VertexBuffer = Renderer::RHI()->CreateVertexBuffer(sizeof(VertexType) * vertex_count, D3D11_USAGE_DEFAULT, &vertex_res);

		int index_count = 3;
		unsigned long indices[3];
		indices[0] = 0;
		indices[1] = 1;
		indices[2] = 2;
		auto index_res = ResourceArray(indices, index_count);
		IndexBuffer = Renderer::RHI()->CreateIndexBuffer(sizeof(unsigned long) * index_count, D3D11_USAGE_DEFAULT, &index_res);

		D3D11_INPUT_ELEMENT_DESC layout[] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		};
		unsigned int num_desc = sizeof(layout) / sizeof(layout[0]);

		VertexShader = Renderer::RHI()->CreateVertexShader("Resource/color.vs", layout, num_desc);
		PixelShader = Renderer::RHI()->CreatePixelShader("Resource/color.ps");
		ConstantBuffer = Renderer::RHI()->CreateConstantBuffer(sizeof(MatrixBufferType));


	}

	virtual void OnUpdate(void) override
	{
		
	}

	virtual void OnDraw(void) override
	{

		Renderer::RHI()->BindVertexBuffer(VertexBuffer, sizeof(VertexType), 0);
		Renderer::RHI()->BindIndexBuffer(IndexBuffer, DXGI_FORMAT_R32_UINT, 0);
		sd.OnDraw();
		
		//{
		//	
		//	D3D11_MAPPED_SUBRESOURCE mappedResource;
		//	Renderer::Instance()->context()->Map(ConstantBuffer->GetResource<ID3D11Buffer>(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
		//	
		//	MatrixBufferType* b = (MatrixBufferType*)mappedResource.pData;
		//	b->projection = *Camera::Instance()->Perspective();
		//	b->view = *Camera::Instance()->View();
		//	XMMATRIX worldMatrix = XMMatrixIdentity();
		//	b->world = XMMatrixIdentity();
		//	Renderer::Instance()->context()->Unmap(ConstantBuffer->GetResource<ID3D11Buffer>(), 0);
		//	Renderer::RHI()->UpdateSubreousrce(ConstantBuffer, &b);
		//}
		//Renderer::RHI()->VSSetConstantBuffers(0, 1, ConstantBuffer);
		//Renderer::RHI()->SetInputLayout(VertexShader);
		//Renderer::RHI()->BindVertexShader(VertexShader);
		//Renderer::RHI()->BindPixelShader(PixelShader);
		//Renderer::RHI()->DrawIndexed(3, 0, 0);
	}
};

