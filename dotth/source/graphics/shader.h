
#pragma once

#include "Framework/Base.h"
#include "Graphics/Renderer.h"

class Shader : public Base
{
protected:
	ID3D11VertexShader* _VertexShader = nullptr;
	ID3D11PixelShader* _PixelShader = nullptr;
	ID3D11InputLayout* _InputLayout = nullptr;
public:
	bool LoadShader(std::string file_name, D3D11_INPUT_ELEMENT_DESC* input_desc = nullptr, unsigned int desc_size = 0);


	void Draw(ID3D11Buffer* buffer, unsigned int size);
};

