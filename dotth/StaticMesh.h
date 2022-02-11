#pragma once

#include "AssetBase.h"

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

	bool Load2(const std::string& key);
};