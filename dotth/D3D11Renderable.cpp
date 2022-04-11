#include "D3D11Renderable.h"

void D3D11Primitive::AddVertexBuffer(void* data, unsigned int typeSize, unsigned int count)
{
	vertexBuffers.emplace_back();
	ID3D11Buffer** buffer = vertexBuffers.back();
	D3D11_BUFFER_DESC desc;
	memset(&desc, 0, sizeof(decltype(desc)));
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.ByteWidth = typeSize * count;
	desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	D3D11_SUBRESOURCE_DATA res;
	memset(&res, 0, sizeof(decltype(res)));
	res.pSysMem = data;
	res.SysMemPitch = 0;
	res.SysMemSlicePitch = 0;
	device->CreateBuffer(&desc, &res, buffer);
	bufferStrides.push_back(typeSize);
}

void D3D11Primitive::SetIndexBuffer(void* data, unsigned int typeSize, unsigned int count)
{
	D3D11_BUFFER_DESC desc;
	memset(&desc, 0, sizeof(decltype(desc)));
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.ByteWidth = typeSize * count;
	desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	D3D11_SUBRESOURCE_DATA res;
	memset(&res, 0, sizeof(decltype(res)));
	res.pSysMem = data;
	res.SysMemPitch = 0;
	res.SysMemSlicePitch = 0;
	device->CreateBuffer(&desc, &res, &indexBuffer);

	indexCount = count;
}

void D3D11Primitive::Draw(void)
{
	unsigned int offset = 0;
	for (unsigned int i = 0; i < vertexBuffers.size(); ++i)
	{
		context->IASetVertexBuffers(i, 1, vertexBuffers[i], &bufferStrides[i], &offset);
	}
	context->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	context->DrawIndexed(indexCount, 0, 0);
}
