
#include "model.h"

void model::reset(void)
{
	_vertex_buffer->Release();
	_index_buffer->Release();

	delete _vertex_buffer;
	delete _index_buffer;
	delete[] _vertex_list;
	delete[] _index_list;

	_vertex_buffer = nullptr;
	_index_buffer = nullptr;
	_vertex_list = nullptr;
	_index_list = nullptr;
	_context = nullptr;
}

void model::draw(void)
{
	if (_context == nullptr)
		return;
	unsigned int stride = sizeof(position_color);
	unsigned int offset = 0;
	_context->IASetVertexBuffers(0, 1, &_vertex_buffer, &stride, &offset);
	_context->IASetIndexBuffer(_index_buffer, DXGI_FORMAT_R32_UINT, 0);
	_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}
