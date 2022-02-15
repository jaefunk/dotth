#pragma once

#include "Renderable.h"

class StaticMesh
{
private:
	std::shared_ptr<dotth::model> Raw;
	std::vector<Renderable*> Renderables;

public:
	unsigned int GetSectionSize(void)
	{
		return static_cast<unsigned int>(Renderables.size());
	}
	bool Load(const std::string& key);
	void Draw(unsigned int index);
};