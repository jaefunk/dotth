#pragma once

#include "Framework/component.h"
#include "graphics/renderer.h"

template <typename vtype>
class drawable_component : public Component
{
protected:
	std::vector<vtype> _vertex_list;
	std::vector<unsigned long> _index_list;
	ID3D11Buffer* _vertex_buff = nullptr;
	ID3D11Buffer* _index_buff = nullptr;
	int _vertex_cnt = 0;
	int _index_cnt = 0;
};

