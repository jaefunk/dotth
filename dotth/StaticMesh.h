#pragma once

#include "Asset3d.h"

class StaticMesh
{
protected:
	std::shared_ptr<model> Raw;

public:
	unsigned int GetSectionSize(void)
	{
		return static_cast<unsigned int>(Raw->sections.size());
	}
	unsigned int GetIndicesSize(int index)
	{
		return static_cast<unsigned int>(Raw->sections[index].indices.size());
	}
	virtual void Load(const std::string& path) = 0;
	virtual void Draw(const unsigned int& index) = 0;
};