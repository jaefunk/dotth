
#pragma once

#include "Graphics/RHI/ResourceRHI.h"


class D11IndexBuffer : public IndexBufferRHI
{
public:
	D11IndexBuffer(ID3D11Buffer* buffer, unsigned int size, unsigned int usage) : IndexBufferRHI(buffer, size, usage) {}
	virtual ~D11IndexBuffer(void) {}
	virtual void Release(void) override
	{
		GetResource<ID3D11Buffer>()->Release();
	}
};

class D11VertexBuffer : public VertexBufferRHI
{
public:
	D11VertexBuffer(ID3D11Buffer* buffer, unsigned int size, unsigned int usage) : VertexBufferRHI(buffer, size, usage) {}
	virtual ~D11VertexBuffer(void) {}
	virtual void Release(void) override
	{
		GetResource<ID3D11Buffer>()->Release();
	}
};

class D11VertexShader : public VertexShaderRHI
{
public:
	ID3D11InputLayout* Layout = nullptr;
public:
	D11VertexShader(ID3D11VertexShader* shader, ID3D11InputLayout* layout) : VertexShaderRHI(shader), Layout(layout) {}
};

class D11PixelShader : public PixelShaderRHI
{
public:
	D11PixelShader(ID3D11PixelShader* shader) : PixelShaderRHI(shader) {}
};