#pragma once

#include "MeshComponent.h"
#include "RawMesh.h"
#include "D3D11Shader.h"
#include "D3D11Camera.h"

class StaticMeshComponent : public MeshComponent
{
private:
	D3D11Camera _Camera;

	ID3D11Buffer* _VertexBuffer = nullptr;
	ID3D11Buffer* _IndexBuffer = nullptr;
	ID3D11Buffer* _ConstantBuffer = nullptr;
	ID3D11VertexShader* _VertexShader = nullptr;
	ID3D11PixelShader* _PixelShader = nullptr;
	ID3D11InputLayout* _InputLayout = nullptr;

private:
	StaticMesh _StaticMesh;

public:
	virtual void OnInit(void) override;
	virtual void OnUpdate(void) override;
	virtual void OnDraw(void) override;
	virtual void OnDestroy(void) override;

public:
	bool LoadShader(std::string file_name, D3D11_INPUT_ELEMENT_DESC* input_desc = nullptr, unsigned int desc_size = 0);
};
