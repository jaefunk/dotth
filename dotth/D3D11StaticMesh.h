#pragma once

#include "StaticMesh.h"
#include "D3D11RHI.h"

class D3D11StaticMesh : public StaticMesh
{
private:
	ID3D11Buffer* _VertexBuffer = nullptr;
	ID3D11Buffer* _IndexBuffer = nullptr;

public:
	virtual void Load(const char* file) override;
	virtual void Draw(void) override;
};

