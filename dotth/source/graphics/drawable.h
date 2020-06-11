
#pragma once

#include "dotth.h"
#include "graphics/renderer.h"
#include "type_vertex.h"

class drawable
{
private:
	std::vector<vertex::position_color> _vertex_list;
	std::vector<unsigned int> _index_list;
	ID3D11Buffer* _vertex_buffer = nullptr;
	ID3D11Buffer* _index_buffer = nullptr;

public:
	bool init_triangle(XMFLOAT4 color = XMFLOAT4(1.f, 0.f, 0.f, 1.f))
	{
		reset();

		// top
		_vertex_list.emplace_back();
		_vertex_list.back().color = color;
		_vertex_list.back().position = XMFLOAT3(0.f, 1.f, 0.f);

		// left bottom
		_vertex_list.emplace_back();
		_vertex_list.back().color = color;
		_vertex_list.back().position = XMFLOAT3(-1.f, -1.f, 0.f);

		// right bottom
		_vertex_list.emplace_back();
		_vertex_list.back().color = color;
		_vertex_list.back().position = XMFLOAT3(1.f, -1.f, 0.f);

		_index_list.push_back(0);
		_index_list.push_back(1);
		_index_list.push_back(2);

		// ���� ���� ������ ����ü�� �����մϴ�.
		D3D11_BUFFER_DESC vertex_buffer_desc;
		vertex_buffer_desc.Usage = D3D11_USAGE_DEFAULT;
		vertex_buffer_desc.ByteWidth = sizeof(vertex::position_color) * static_cast<unsigned int>(_vertex_list.size());
		vertex_buffer_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		vertex_buffer_desc.CPUAccessFlags = 0;
		vertex_buffer_desc.MiscFlags = 0;
		vertex_buffer_desc.StructureByteStride = 0;

		// subresource ������ ���� �����Ϳ� ���� �����͸� �����մϴ�.
		D3D11_SUBRESOURCE_DATA vertex_data;
		vertex_data.pSysMem = _vertex_list.data();
		vertex_data.SysMemPitch = 0;
		vertex_data.SysMemSlicePitch = 0;

		// ���� ���� ���۸� ����ϴ�.
		if (FAILED(renderer::get()->dx11()->device()->CreateBuffer(&vertex_buffer_desc, &vertex_data, &_vertex_buffer)))
		{
			return false;
		}

		// ���� �ε��� ������ ����ü�� �����մϴ�.
		D3D11_BUFFER_DESC indexBufferDesc;
		indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		indexBufferDesc.ByteWidth = sizeof(unsigned int) * static_cast<unsigned int>(_index_list.size());
		indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		indexBufferDesc.CPUAccessFlags = 0;
		indexBufferDesc.MiscFlags = 0;
		indexBufferDesc.StructureByteStride = 0;

		// �ε��� �����͸� ����Ű�� ���� ���ҽ� ����ü�� �ۼ��մϴ�.
		D3D11_SUBRESOURCE_DATA indexData;
		indexData.pSysMem = _index_list.data();
		indexData.SysMemPitch = 0;
		indexData.SysMemSlicePitch = 0;

		// �ε��� ���۸� �����մϴ�.
		if (FAILED(renderer::get()->dx11()->device()->CreateBuffer(&indexBufferDesc, &indexData, &_index_buffer)))
		{
			return false;
		}
		return true;
	}

	void reset(void)
	{
		_vertex_list.clear();
		_index_list.clear();
	}

	void draw(ID3D11DeviceContext* ctx)
	{
		// ���� ������ ������ �������� �����մϴ�.
		unsigned int stride = sizeof(vertex::position_color);
		unsigned int offset = 0;

		// ������ �� �� �ֵ��� �Է� ��������� ���� ���۸� Ȱ������ �����մϴ�.
		ctx->IASetVertexBuffers(0, 1, &_vertex_buffer, &stride, &offset);

		// ������ �� �� �ֵ��� �Է� ��������� �ε��� ���۸� Ȱ������ �����մϴ�.
		ctx->IASetIndexBuffer(_index_buffer, DXGI_FORMAT_R32_UINT, 0);

		// ���� ���۷� �׸� �⺻���� �����մϴ�. ���⼭�� �ﰢ������ �����մϴ�.
		ctx->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		return;
	}
};