#pragma once

#include "StaticMesh.h"
#include "D3D11RHI.h"

class D3D11StaticMesh : public StaticMesh
{
private:
	ID3D11Buffer* _VertexBuffer = nullptr;
	ID3D11Buffer* _IndexBuffer = nullptr;
	ID3D11Buffer* _ConstantBuffer = nullptr;
	ID3D11VertexShader* _VertexShader = nullptr;
	ID3D11PixelShader* _PixelShader = nullptr;
	ID3D11InputLayout* _InputLayout = nullptr;

private:
	virtual bool LoadShader(std::string file_name) override;

public:
	virtual void Load(const char* file) override;
	virtual void Draw(void) override;
};

