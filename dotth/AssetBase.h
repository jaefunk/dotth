#pragma once

#include "dotth.h"

enum class EXTENSION_TYPE {	
	JPEG,
	FBX,
};

struct R8G8B8A8 {
	union {
		struct {
			unsigned char R, G, B, A;
		};
		struct {
			unsigned int Alignment;
		};
	};

	R8G8B8A8(void) : Alignment(0)
	{

	}

	R8G8B8A8(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha)
		: R(red), G(green), B(blue), A(alpha)
	{
	}
};

struct Vertice {
	Vector3 position;
	Vector3 normal;
	Vector2 textureCoord;
	Vector3 tangent;
	Vector3 bitangent;
	Vector4 color;
};

class Resource
{
public:
	virtual std::shared_ptr<Resource> Clone(void) = 0;
};

class Mesh : public Resource
{
public:
	struct PrimitiveNode
	{
		unsigned int materialID;
		std::vector<Vertice> vertices;
		std::vector<unsigned int> indices;
		unsigned int GetVerticeByteWidth(void) const
		{
			return static_cast<unsigned int>(sizeof(Vertice) * vertices.size());
		}
		unsigned int GetIndiceByteWidth(void) const
		{
			return static_cast<unsigned int>(sizeof(unsigned int) * indices.size());
		}
	};
	std::vector<PrimitiveNode> primitiveNodes;

public:
	virtual std::shared_ptr<Resource> Clone(void) override
	{
		auto p = std::make_shared<Mesh>();
		p->primitiveNodes = this->primitiveNodes;
		return p;
	}
};

class Texture : public Resource
{
public:
	virtual std::shared_ptr<Resource> Clone(void) override
	{
		auto p = std::make_shared<Texture>();
		p->ComponentCount = this->ComponentCount;
		p->Width = this->Width;
		p->Height = this->Height;
		p->Texels = this->Texels;
		return p;
	}

public:
	unsigned int ComponentCount;
	unsigned int Width;
	unsigned int Height;
	std::vector<R8G8B8A8> Texels;

public:
	void* GetSysMem(void)
	{
		return static_cast<void*>(Texels.data());
	}
	unsigned int GetSysMemPitch(void)
	{
		return Width * static_cast<unsigned int>(sizeof(R8G8B8A8));
	}
};

class FBXLoader
{
public:
	static std::unique_ptr<Mesh> Load(const std::string& filePath);
};

class JPEGLoader
{
public:
	static std::unique_ptr<Texture> Load(const std::string& filePath);
};