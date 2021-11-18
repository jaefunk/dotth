#pragma once

#include "AssetBase.h"

struct Vertice {
	Vector3 position;
	Vector3 normal;
	Vector2 textureCoord;
	Vector3 tangent;
	Vector3 bitangent;
	Vector4 color;
};

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

class Mesh : public Resource
{
public:
	std::vector<PrimitiveNode> primitiveNodes;

public:
	virtual std::shared_ptr<Resource> Clone(void) override
	{
		auto p = std::make_shared<Mesh>();
		p->primitiveNodes = this->primitiveNodes;
		return p;
	}
};

class FBXLoader 
{
public:
	static std::unique_ptr<Mesh> Load(const std::string& filePath);
};