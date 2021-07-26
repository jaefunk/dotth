#pragma once

#include "Asset3d.h"

class StaticMesh : public ModelBase
{
public:
	virtual void Initialize(void) {}
	virtual unsigned int GetSectionSize(void) = 0;
	virtual unsigned int GetIndicesSize(int index) = 0;
	virtual bool Load(const std::string& path) = 0;
	virtual void Draw(const unsigned int& index) = 0;
};