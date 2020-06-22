
#include "polygon.h"

bool polygon::Initialize(void)
{
	// ���� �迭�� ���� ���� �����մϴ�.
	_vertex_cnt = 3;

	// �ε��� �迭�� �ε��� ���� �����մϴ�.
	_index_cnt = 3;

	// ���� �迭�� ����ϴ�.
	vertex_type* vertices = new vertex_type[_vertex_cnt];
	if (!vertices)
	{
		return false;
	}

	// �ε��� �迭�� ����ϴ�.
	unsigned long* indices = new unsigned long[_index_cnt];
	if (!indices)
	{
		return false;
	}

	// ���� �迭�� �����͸� �����մϴ�.
	vertices[0].position = XMFLOAT3(1.0f, 1.0f, 0.0f);  // Top middle.
	vertices[0].color = XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);

	vertices[1].position = XMFLOAT3(1.0f, -1.0f, 0.0f);  // Bottom right.
	vertices[1].color = XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);

	vertices[2].position = XMFLOAT3(-1.0f, -1.0f, 0.0f);  // Bottom left.
	vertices[2].color = XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f);



	// �ε��� �迭�� ���� �����մϴ�.
	indices[0] = 0;  // Bottom left.
	indices[1] = 1;  // Top middle.
	indices[2] = 2;  // Bottom right.

	// ���� ���� ������ ����ü�� �����մϴ�.
	D3D11_BUFFER_DESC vertexBufferDesc;
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(vertex_type) * _vertex_cnt;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

	// subresource ������ ���� �����Ϳ� ���� �����͸� �����մϴ�.
	D3D11_SUBRESOURCE_DATA vertexData;
	vertexData.pSysMem = vertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	// ���� ���� ���۸� ����ϴ�.
	if (FAILED(renderer::device()->CreateBuffer(&vertexBufferDesc, &vertexData, &_vertex_buff)))
	{
		return false;
	}

	// ���� �ε��� ������ ����ü�� �����մϴ�.
	D3D11_BUFFER_DESC indexBufferDesc;
	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(unsigned long) * _index_cnt;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;

	// �ε��� �����͸� ����Ű�� ���� ���ҽ� ����ü�� �ۼ��մϴ�.
	D3D11_SUBRESOURCE_DATA indexData;
	indexData.pSysMem = indices;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	// �ε��� ���۸� �����մϴ�.
	if (FAILED(renderer::device()->CreateBuffer(&indexBufferDesc, &indexData, &_index_buff)))
	{
		return false;
	}

	// �����ǰ� ���� �Ҵ�� ���� ���ۿ� �ε��� ���۸� �����մϴ�.
	delete[] vertices;
	vertices = 0;

	delete[] indices;
	indices = 0;

	return true;
}


void polygon::Shutdown()
{
	// �ε��� ���۸� �����մϴ�.
	if (_index_buff)
	{
		_index_buff->Release();
		_index_buff = 0;
	}

	// ���� ���۸� �����մϴ�.
	if (_vertex_buff)
	{
		_vertex_buff->Release();
		_vertex_buff = 0;
	}
}


void polygon::Render(void)
{
	// ���� ������ ������ �������� �����մϴ�.
	unsigned int stride = sizeof(vertex_type);
	unsigned int offset = 0;

	// ������ �� �� �ֵ��� �Է� ��������� ���� ���۸� Ȱ������ �����մϴ�.
	renderer::context()->IASetVertexBuffers(0, 1, &_vertex_buff, &stride, &offset);

	// ������ �� �� �ֵ��� �Է� ��������� �ε��� ���۸� Ȱ������ �����մϴ�.
	renderer::context()->IASetIndexBuffer(_index_buff, DXGI_FORMAT_R32_UINT, 0);

	// ���� ���۷� �׸� �⺻���� �����մϴ�. ���⼭�� �ﰢ������ �����մϴ�.
	renderer::context()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}


int polygon::GetIndexCount()
{
	return _index_cnt;
}