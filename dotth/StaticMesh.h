#pragma once

#include "Asset3d.h"

class StaticMesh : public Mesh
{
private:
	std::vector<ID3D11Buffer*> vertexBuffers;
	std::vector<ID3D11Buffer*> indexBuffers;

public:
	virtual void Initialize(void) {}
	virtual unsigned int GetSectionSize(void);
	virtual unsigned int GetIndicesSize(int index);
	virtual bool Load(const std::string& key);
	virtual void Draw(unsigned int index);
};