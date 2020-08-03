
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
private:
	void* _Resource;

public:
	ResourceRHI(void) = default;
	ResourceRHI(void* resource) : _Resource(resource) {}

public:
	template <class Ty>
	Ty* GetResource(void)
	{
		return static_cast<Ty*>(_Resource);
	}
};

class IndexBufferRHI : public ResourceRHI
{
private:
	unsigned int _Size;
	unsigned int _Usage;
public:
	IndexBufferRHI(void* resource, unsigned int size, unsigned int usage) : ResourceRHI(resource), _Size(size), _Usage(usage) {}
	unsigned int GetSize() const { return _Size; }
	unsigned int GetUsage() const { return _Usage; }
};

class VertexBufferRHI : public ResourceRHI
{
private:
	unsigned int _Size;
	unsigned int _Usage;
public:
	VertexBufferRHI(void* resource, unsigned int size, unsigned int usage) : ResourceRHI(resource), _Size(size), _Usage(usage) {}
	unsigned int GetSize() const { return _Size; }
	unsigned int GetUsage() const { return _Usage; }
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