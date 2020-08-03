
#include "model.h"

bool model::Initialize(void)
{
	// 정점 배열의 정점 수를 설정합니다.
	int vertex_count = 3;
	//VertexType* vertices = new VertexType[3];
	VertexType vertices[3];
	vertices[0].position = XMFLOAT3(0.0f, 1.0f, 0.0f);  // Top middle.
	vertices[0].color = XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);
	vertices[1].position = XMFLOAT3(1.0f, -1.0f, 0.0f);  // Bottom right.
	vertices[1].color = XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);
	vertices[2].position = XMFLOAT3(-1.0f, -1.0f, 0.0f);  // Bottom left.
	vertices[2].color = XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f);

	auto res = ResourceArray(vertices, vertex_count);
	auto vertex_buffer = Renderer::RHI()->CreateVertexBuffer(sizeof(VertexType) * vertex_count, D3D11_USAGE_DEFAULT, &res);
	m_vertexBuffer = vertex_buffer->GetResource<ID3D11Buffer>();
	

	int index_count = 3;	

	unsigned long indices[3];
	indices[0] = 0;  // Bottom left.
	indices[1] = 1;  // Top middle.
	indices[2] = 2;  // Bottom right.

	auto index_res = ResourceArray(indices, index_count);

	auto index_buffer = Renderer::RHI()->CreateIndexBuffer(sizeof(unsigned long) * index_count, D3D11_USAGE_DEFAULT, &index_res);
	m_indexBuffer = index_buffer->GetResource<ID3D11Buffer>();

	return true;
}


void model::Shutdown()
{
	// 인덱스 버퍼를 해제합니다.
	if (m_indexBuffer)
	{
		m_indexBuffer->Release();
		m_indexBuffer = 0;
	}

	// 정점 버퍼를 해제합니다.
	if (m_vertexBuffer)
	{
		m_vertexBuffer->Release();
		m_vertexBuffer = 0;
	}
}


void model::Render(void)
{
	// 정점 버퍼의 단위와 오프셋을 설정합니다.
	unsigned int stride = sizeof(VertexType);
	unsigned int offset = 0;

	// 렌더링 할 수 있도록 입력 어셈블러에서 정점 버퍼를 활성으로 설정합니다.
	Renderer::context()->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);

	// 렌더링 할 수 있도록 입력 어셈블러에서 인덱스 버퍼를 활성으로 설정합니다.
	Renderer::context()->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);

	// 정점 버퍼로 그릴 기본형을 설정합니다. 여기서는 삼각형으로 설정합니다.
	Renderer::context()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}


int model::GetIndexCount()
{
	return m_indexCount;
}