#pragma once

#include "StaticMesh.h"
#include "D3D11RHI.h"

class D3D11StaticMesh : public StaticMesh
{
protected:
	std::vector<ID3D11Buffer*> _VertexBuffers;
	std::vector<ID3D11Buffer*> _IndexBuffers;

public:
	virtual unsigned int GetSectionSize(void) override;
	virtual unsigned int GetIndicesSize(int index) override;

public:
	virtual bool Load(const std::string& key) override;
	virtual void Draw(const unsigned int& index) override;
};