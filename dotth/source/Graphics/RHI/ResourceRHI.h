
#pragma once

class IDataSize
{
public:
	virtual ~IDataSize(void) {}
	virtual const void* GetData(void) const = 0;
	virtual unsigned int GetSize(void) const = 0;
};

class ResourceArray : public IDataSize
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
private:
	void* _Resource;

public:
	ResourceRHI(void) = default;
	ResourceRHI(void* resource) : _Resource(resource) {}
	virtual ~ResourceRHI(void) {}
public:
	template <class Ty>
	Ty* GetResource(void)
	{
		return static_cast<Ty*>(_Resource);
	}
	virtual void Release(void) {}
};

class BufferRHI : public ResourceRHI
{
private:
	unsigned int _Size;
	unsigned int _Usage;
public:
	BufferRHI(void* resource, unsigned int size, unsigned int usage) : ResourceRHI(resource), _Size(size), _Usage(usage) {}
	virtual ~BufferRHI(void) {}
	unsigned int GetSize() const { return _Size; }
	unsigned int GetUsage() const { return _Usage; }
};

class VertexBufferRHI : public BufferRHI
{
public:
	VertexBufferRHI(void* resource, unsigned int size, unsigned int usage) : BufferRHI(resource, size, usage) {}
};

class IndexBufferRHI : public BufferRHI
{
public:
	IndexBufferRHI(void* resource, unsigned int size, unsigned int usage) : BufferRHI(resource, size, usage) {}
};

class ShaderRHI : public ResourceRHI
{
public:
	ShaderRHI(void* resource) : ResourceRHI(resource) {}
};

class VertexShaderRHI : public ShaderRHI
{
public:
	VertexShaderRHI(void* resource) : ShaderRHI(resource) {}
};

class PixelShaderRHI : public ShaderRHI
{
public:
	PixelShaderRHI(void* resource) : ShaderRHI(resource) {}
};