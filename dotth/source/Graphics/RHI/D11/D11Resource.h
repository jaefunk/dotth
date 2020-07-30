
#pragma once

#include "Graphics/RHI/ResourceRHI.h"

class D11Resource : public ResourceRHI
{

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

class D11IndexBuffer : public IndexBufferRHI
{

};

class D11VertexBuffer : public VertexBufferRHI
{
public:
	ID3D11Buffer* _Resource;
public:
	D11VertexBuffer(ID3D11Buffer* buffer, unsigned int size, unsigned int usage) : VertexBufferRHI(size, usage), _Resource(buffer) {}
};