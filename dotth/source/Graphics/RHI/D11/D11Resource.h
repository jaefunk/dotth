
#pragma once

#include "Graphics/RHI/ResourceRHI.h"

class D11IndexBuffer : public IndexBufferRHI
{
public:
	D11IndexBuffer(ID3D11Buffer* buffer, unsigned int size, unsigned int usage) : IndexBufferRHI(buffer, size, usage) {}
};

class D11VertexBuffer : public VertexBufferRHI
{
public:
	D11VertexBuffer(ID3D11Buffer* buffer, unsigned int size, unsigned int usage) : VertexBufferRHI(buffer, size, usage) {}
};

class D11Shader : public ShaderRHI
{

};

class D11VertexShader : public VertexShaderRHI
{

};

class D11PixelShader : public PixelShaderRHI
{

};