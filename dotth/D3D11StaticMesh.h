#pragma once

#include "StaticMesh.h"
#include "D3D11RHI.h"

class D3D11StaticMesh : public StaticMesh
{
private:
	std::vector<ID3D11Buffer*> _VertexBuffers;
	std::vector<ID3D11Buffer*> _IndexBuffers;

public:
	void Load(const std::string& key);
	virtual void Draw(const unsigned int& index) override;
};