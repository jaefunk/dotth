#pragma once

#include "RawMesh.h"

class StaticMesh : public Mesh
{
public:
	virtual bool LoadShader(std::string file_name) { return true; };
	virtual void Load(const char* file) {}
	virtual void Draw(void) {};
};