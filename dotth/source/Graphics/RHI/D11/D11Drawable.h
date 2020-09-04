
#pragma once

#include "Graphics/RHI/DrawableRHI.h"

class D11Drawable : public DrawableRHI
{
public:
	D11Drawable(void);

private:
	ID3D11Buffer* _VertexBuffer = nullptr;
	ID3D11Buffer* _IndexBuffer = nullptr;
	ID3D11Buffer* _ConstantBuffer = nullptr;
	unsigned int _VertexCount = 0;
	unsigned int _IndexCount = 0;
	size_t _VertexTypeSize = 0;
	size_t _IndexTypeSize = 0;

public:
	void Validate(void)
	{

	}
};