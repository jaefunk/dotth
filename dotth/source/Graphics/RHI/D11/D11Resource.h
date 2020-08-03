
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

class D11Buffer
{
private:
	ID3D11Buffer* _Resource;
public:
	D11Buffer(ID3D11Buffer* buffer) : _Resource(buffer) {}
	void* GetResource(void) { return _Resource; }
}; 

class D11IndexBuffer : public IndexBufferRHI, public D11Buffer
{
public:
	D11IndexBuffer(ID3D11Buffer* buffer, unsigned int size, unsigned int usage) : IndexBufferRHI(size, usage), D11Buffer(buffer) {}
};

class D11VertexBuffer : public VertexBufferRHI, public D11Buffer
{
public:
	D11VertexBuffer(ID3D11Buffer* buffer, unsigned int size, unsigned int usage) : VertexBufferRHI(size, usage), D11Buffer(buffer) {}
};