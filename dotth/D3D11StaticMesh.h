#pragma once

#include "StaticMesh.h"
#include "D3D11RHI.h"

class D3D11StaticMesh : public StaticMesh
{
private:
	std::vector<ID3D11Buffer*> _VertexBuffers;
	std::vector<ID3D11Buffer*> _IndexBuffers;

public:
	virtual unsigned int GetSectionSize(void) override;
	virtual unsigned int GetIndicesSize(int index) override;

public:
	virtual void Load(std::shared_ptr<model> raw) override;
	virtual void Load(const std::string& key) override;
	virtual void Draw(const unsigned int& index) override;
};