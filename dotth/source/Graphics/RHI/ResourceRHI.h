
#pragma once

class IResourceArray
{
public:
	virtual ~IResourceArray(void) {}
	virtual const void* GetData(void) const = 0;
	virtual unsigned int GetSize(void) const = 0;
};

class ResourceArray : public IResourceArray
{
private:
	const void* _Data;
	unsigned int _Size;
public:
	ResourceArray(const void* data, unsigned int size) : _Data(data), _Size(size) {}
public:
	virtual const void* GetData(void) const { return _Data; };
	virtual unsigned int GetSize(void) const { return _Size; }
};

class ResourceRHI
{

};

class ShaderRHI : public ResourceRHI
{

};

class VertexShaderRHI : public ShaderRHI
{

};

class PixelShaderRHI : public ShaderRHI
{

};

class IndexBufferRHI : public ResourceRHI
{
private:
	unsigned int _Size;
	unsigned int _Usage;
public:
	IndexBufferRHI(unsigned int size, unsigned int usage) : _Size(size), _Usage(usage) {}
	unsigned int GetSize() const { return _Size; }
	unsigned int GetUsage() const { return _Usage; }
};

class VertexBufferRHI : public ResourceRHI
{
private:
	unsigned int _Size;
	unsigned int _Usage;
public:
	VertexBufferRHI(unsigned int size, unsigned int usage) : _Size(size), _Usage(usage) {}
	unsigned int GetSize() const { return _Size; }
	unsigned int GetUsage() const { return _Usage; }
};