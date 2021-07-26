#include "D3D11OrthoRect.h"




bool D3D11OrthoRect::Initialize(ID3D11Device* device, int width, int height)
{
	float left = (float)((width / 2) * -1);

	float right = left + (float)width;

	float top = (float)(height / 2);

	float bottom = top - (float)height;

	_VertexCount = 4;
	_IndexCount = 6;

	VertexType* vertices = new VertexType[_VertexCount];
	if (!vertices)
	{
		return false;
	}

	unsigned long* indices = new unsigned long[_IndexCount];
	if (!indices)
	{
		return false;
	}

	vertices[0].position = XMFLOAT3(left, top, 0.0f);
	vertices[0].texture = XMFLOAT2(0.0f, 0.0f);

	vertices[1].position = XMFLOAT3(right, top, 0.0f);
	vertices[1].texture = XMFLOAT2(1.0f, 0.0f);

	vertices[2].position = XMFLOAT3(left, bottom, 0.0f);
	vertices[2].texture = XMFLOAT2(0.0f, 1.0f);

	vertices[3].position = XMFLOAT3(right, bottom, 0.0f);
	vertices[3].texture = XMFLOAT2(1.0f, 1.0f);

	indices[0] = 0;
	indices[1] = 1;
	indices[2] = 2;
	indices[3] = 1;
	indices[4] = 3;
	indices[5] = 2;

	D3D11_BUFFER_DESC vertexBufferDesc;
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(VertexType) * _VertexCount;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA vertexData;
	vertexData.pSysMem = vertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	if (FAILED(device->CreateBuffer(&vertexBufferDesc, &vertexData, &_VertexBuffer)))
	{
		return false;
	}

	D3D11_BUFFER_DESC indexBufferDesc;
	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(unsigned long) * _IndexCount;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA indexData;
	indexData.pSysMem = indices;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	if (FAILED(device->CreateBuffer(&indexBufferDesc, &indexData, &_IndexBuffer)))
	{
		return false;
	}

	delete[] vertices;
	vertices = 0;

	delete[] indices;
	indices = 0;

	return true;
}


void D3D11OrthoRect::Shutdown()
{
	if (_IndexBuffer)
	{
		_IndexBuffer->Release();
		_IndexBuffer = nullptr;
	}

	if (_VertexBuffer)
	{
		_VertexBuffer->Release();
		_VertexBuffer = nullptr;
	}
}


void D3D11OrthoRect::Render(ID3D11DeviceContext* context)
{
	unsigned int stride = sizeof(VertexType);
	unsigned int offset = 0;
	context->IASetVertexBuffers(0, 1, &_VertexBuffer, &stride, &offset);
	context->IASetIndexBuffer(_IndexBuffer, DXGI_FORMAT_R32_UINT, 0);
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}


int D3D11OrthoRect::GetIndexCount()
{
	return _IndexCount;
}
