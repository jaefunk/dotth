#pragma once


#include "Shader.h"
#include "D3D11RHI.h"

class D3D11Shader : public Shader
{
private:
	ID3D11Buffer* _ConstantBuffer = nullptr;
	ID3D11VertexShader* _VertexShader = nullptr;
	ID3D11PixelShader* _PixelShader = nullptr;
	ID3D11InputLayout* _InputLayout = nullptr;


	ID3D11ShaderResourceView* _SRV = nullptr;

public:
	virtual bool Load(const char* FileName) override;
	virtual void Draw(const Matrix& matrix, unsigned int size) override;
};
