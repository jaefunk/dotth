#pragma once

#include "StaticMesh.h"
#include "D3D11RHI.h"

class D3D11StaticMesh : public StaticMesh
{
private:
	std::vector<ID3D11Buffer*> _VertexBuffers;
	std::vector<ID3D11Buffer*> _IndexBuffers;

public:
	virtual void Load(const std::string& path) override;
	virtual void Draw(const unsigned int& index) override;
};