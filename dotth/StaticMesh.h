#pragma once

#include "Asset3d.h"

class StaticMesh
{
public:
	virtual unsigned int GetSectionSize(void) = 0;
	virtual unsigned int GetIndicesSize(int index) = 0;
	virtual void Load(std::shared_ptr<model> raw) = 0;
	virtual void Load(const std::string& path) = 0;
	virtual void Draw(const unsigned int& index) = 0;
};