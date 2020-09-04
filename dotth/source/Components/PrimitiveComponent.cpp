
#include "PrimitiveComponent.h"

void PrimitiveComponent::OnInit(void)
{
	{
		D3D11_BUFFER_DESC desc;
		memset(&desc, 0, sizeof(decltype(desc)));
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.ByteWidth = GetVertexStructureSize() * GetVertexCount();
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		D3D11_SUBRESOURCE_DATA data;
		memset(&data, 0, sizeof(decltype(data)));
		void* vertices = GetVertexArray();
		data.pSysMem = vertices;
		data.SysMemPitch = 0;
		data.SysMemSlicePitch = 0;
		_VertexBuffer = Renderer::RHI()->CreateVertexBuffer(desc, data);
		//delete[] vertices;
	}

	{
		D3D11_BUFFER_DESC desc;
		memset(&desc, 0, sizeof(decltype(desc)));
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.ByteWidth = sizeof(unsigned long) * GetIndexCount();
		desc.BindFlags = D3D11_BIND_INDEX_BUFFER;

		D3D11_SUBRESOURCE_DATA data;
		memset(&data, 0, sizeof(decltype(data)));
		unsigned long* indices = GetIndexArray();
		data.pSysMem = indices;
		data.SysMemPitch = 0;
		data.SysMemSlicePitch = 0;
		_IndexBuffer = Renderer::RHI()->CreateIndexBuffer(desc, data);
		//delete[] indices;
	}

	{
		unsigned int size;
		D3D11_INPUT_ELEMENT_DESC* layout;// = nullptr;
		GetInputDesc(&layout, size);
		//D3D11_INPUT_ELEMENT_DESC layout[] = 
		//{
		//	{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		//	{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		//};
		//unsigned int num_desc = sizeof(layout) / sizeof(layout[0]);
		_Shader.LoadShader(GetShaderName(), layout, 2);
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

void PrimitiveComponent::OnUpdate(void)
{

}

void PrimitiveComponent::OnDraw(void)
{
	Renderer::RHI()->BindVertexBuffer(_VertexBuffer, GetVertexStructureSize(), 0);
	Renderer::RHI()->BindIndexBuffer(_IndexBuffer, DXGI_FORMAT_R32_UINT, 0);


	static float fX = 0.f;
	static float fY = 0.f;

	MatrixBufferType cb;
	cb.view = DirectX::XMMatrixTranspose(*Camera::Instance()->View());
	cb.projection = DirectX::XMMatrixTranspose(*Camera::Instance()->Perspective());
	auto world = DirectX::XMMatrixRotationY(fX);
	world = world * DirectX::XMMatrixRotationZ(fY);

	fX += 0.0005f;
	fY += 0.001f;
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

	_Shader.Draw(_ConstantBuffer, GetIndexCount());
}
