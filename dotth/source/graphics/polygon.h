
#pragma once

#include "components/drawable_component.h"

struct vertex_type {
	XMFLOAT3 position = XMFLOAT3(0.f, 0.f, 0.f);
	XMFLOAT4 color = XMFLOAT4(1.f, 1.f, 1.f, 1.f);
};

class polygon : public drawable_component<vertex_type>
{
public:

	virtual void OnInit(void) override
	{
	}
	virtual void OnUpdate(void) override
	{
	}
	virtual void OnDraw(void) override
	{
		unsigned int stride = sizeof(vertex_type);
		unsigned int offset = 0;
		renderer::context()->IASetVertexBuffers(0, 1, &_vertex_buff, &stride, &offset);
		renderer::context()->IASetIndexBuffer(_index_buff, DXGI_FORMAT_R32_UINT, 0);
		renderer::context()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		//renderer::context()->IASetInputLayout(m_layout);
		//renderer::context()->VSSetShader(m_vertexShader, NULL, 0);
		//renderer::context()->PSSetShader(m_pixelShader, NULL, 0);
		//renderer::context()->DrawIndexed(indexCount, 0, 0);
	}
	virtual void OnDestroy(void) override
	{
	}

public:
	void push_vertex(vertex_type vertex)
	{
		_vertex_list.push_back(vertex);
	}
	void push_index(unsigned long index)
	{
		_index_list.push_back(index);
	}
	void reset(void)
	{
		_index_list.clear();
		if (_index_buff != nullptr)
		{
			_index_buff->Release();
			_index_buff = nullptr;
		}

		_vertex_list.clear();
		if (_vertex_buff != nullptr)
		{
			_vertex_buff->Release();
			_vertex_buff = nullptr;
		}
	}

	bool validate(void)
	{
		if (_vertex_list.empty() || _index_list.empty())
			return false;
		
		D3D11_BUFFER_DESC vertexBufferDesc;
		vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		vertexBufferDesc.ByteWidth = sizeof(vertex_type) * _vertex_list.size();
		vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		vertexBufferDesc.CPUAccessFlags = 0;
		vertexBufferDesc.MiscFlags = 0;
		vertexBufferDesc.StructureByteStride = 0;
		D3D11_SUBRESOURCE_DATA vertexData;
		vertexData.pSysMem = _vertex_list.data();
		vertexData.SysMemPitch = 0;
		vertexData.SysMemSlicePitch = 0;
		renderer::device()->CreateBuffer(&vertexBufferDesc, &vertexData, &_vertex_buff);

		
		D3D11_BUFFER_DESC indexBufferDesc;
		indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		indexBufferDesc.ByteWidth = sizeof(unsigned long) * _index_list.size();
		indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		indexBufferDesc.CPUAccessFlags = 0;
		indexBufferDesc.MiscFlags = 0;
		indexBufferDesc.StructureByteStride = 0;
		D3D11_SUBRESOURCE_DATA indexData;
		indexData.pSysMem = _index_list.data();
		indexData.SysMemPitch = 0;
		indexData.SysMemSlicePitch = 0;
		renderer::device()->CreateBuffer(&indexBufferDesc, &indexData, &_index_buff);

		return true;
	}


	bool Initialize(void);
	void Shutdown();
	void Render(void);
	int GetIndexCount();

};
