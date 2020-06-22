
#include "polygon.h"

bool polygon::Initialize(void)
{
	// 정점 배열의 정점 수를 설정합니다.
	_vertex_cnt = 3;

	// 인덱스 배열의 인덱스 수를 설정합니다.
	_index_cnt = 3;

	// 정점 배열을 만듭니다.
	vertex_type* vertices = new vertex_type[_vertex_cnt];
	if (!vertices)
	{
		return false;
	}

	// 인덱스 배열을 만듭니다.
	unsigned long* indices = new unsigned long[_index_cnt];
	if (!indices)
	{
		return false;
	}

	// 정점 배열에 데이터를 설정합니다.
	vertices[0].position = XMFLOAT3(1.0f, 1.0f, 0.0f);  // Top middle.
	vertices[0].color = XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);

	vertices[1].position = XMFLOAT3(1.0f, -1.0f, 0.0f);  // Bottom right.
	vertices[1].color = XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);

	vertices[2].position = XMFLOAT3(-1.0f, -1.0f, 0.0f);  // Bottom left.
	vertices[2].color = XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f);



	// 인덱스 배열의 값을 설정합니다.
	indices[0] = 0;  // Bottom left.
	indices[1] = 1;  // Top middle.
	indices[2] = 2;  // Bottom right.

	// 정적 정점 버퍼의 구조체를 설정합니다.
	D3D11_BUFFER_DESC vertexBufferDesc;
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(vertex_type) * _vertex_cnt;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

	// subresource 구조에 정점 데이터에 대한 포인터를 제공합니다.
	D3D11_SUBRESOURCE_DATA vertexData;
	vertexData.pSysMem = vertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	// 이제 정점 버퍼를 만듭니다.
	if (FAILED(renderer::device()->CreateBuffer(&vertexBufferDesc, &vertexData, &_vertex_buff)))
	{
		return false;
	}

	// 정적 인덱스 버퍼의 구조체를 설정합니다.
	D3D11_BUFFER_DESC indexBufferDesc;
	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(unsigned long) * _index_cnt;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;

	// 인덱스 데이터를 가리키는 보조 리소스 구조체를 작성합니다.
	D3D11_SUBRESOURCE_DATA indexData;
	indexData.pSysMem = indices;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	// 인덱스 버퍼를 생성합니다.
	if (FAILED(renderer::device()->CreateBuffer(&indexBufferDesc, &indexData, &_index_buff)))
	{
		return false;
	}

	// 생성되고 값이 할당된 정점 버퍼와 인덱스 버퍼를 해제합니다.
	delete[] vertices;
	vertices = 0;

	delete[] indices;
	indices = 0;

	return true;
}


void polygon::Shutdown()
{
	// 인덱스 버퍼를 해제합니다.
	if (_index_buff)
	{
		_index_buff->Release();
		_index_buff = 0;
	}

	// 정점 버퍼를 해제합니다.
	if (_vertex_buff)
	{
		_vertex_buff->Release();
		_vertex_buff = 0;
	}
}


void polygon::Render(void)
{
	// 정점 버퍼의 단위와 오프셋을 설정합니다.
	unsigned int stride = sizeof(vertex_type);
	unsigned int offset = 0;

	// 렌더링 할 수 있도록 입력 어셈블러에서 정점 버퍼를 활성으로 설정합니다.
	renderer::context()->IASetVertexBuffers(0, 1, &_vertex_buff, &stride, &offset);

	// 렌더링 할 수 있도록 입력 어셈블러에서 인덱스 버퍼를 활성으로 설정합니다.
	renderer::context()->IASetIndexBuffer(_index_buff, DXGI_FORMAT_R32_UINT, 0);

	// 정점 버퍼로 그릴 기본형을 설정합니다. 여기서는 삼각형으로 설정합니다.
	renderer::context()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}


int polygon::GetIndexCount()
{
	return _index_cnt;
}