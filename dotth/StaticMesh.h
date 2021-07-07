#pragma once

#include "RawMesh.h"

class StaticMesh : public model
{
public:
	unsigned int GetSectionSize(void)
	{
		return static_cast<unsigned int>(sections.size());
	}
	unsigned int GetIndicesSize(int index)
	{
		return static_cast<unsigned int>(sections[index].indices.size());
	}
	virtual void Load(const std::string& path) {}
	virtual void Draw(const unsigned int& index) {}
};