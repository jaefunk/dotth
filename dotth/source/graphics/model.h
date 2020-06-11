
#pragma once

#include "framework/base.h"
#include "graphics/renderer.h"
#include "graphics/type_vertex.h"

class model : public base
{
private:
	ID3D11DeviceContext* _context = nullptr;
	position_color* _vertex_list = nullptr;
	ID3D11Buffer* _vertex_buffer = nullptr;
	unsigned int* _index_list = nullptr;
	ID3D11Buffer* _index_buffer = nullptr;

public:
	void init(ID3D11DeviceContext* context)
	{
		_context = context;
	}
	void init_polygon(void);
	void init_recangle(void);
	void init_cube(void);
	void reset(void);
	void draw(void);
};

