#pragma once

#include "AssetBase.h"

struct Vertice {
	Float3 position;
	Float3 normal;
	Float2 textureCoord;
	Float3 tangent;
	Float3 bitangent;
	Float4 color;
};

struct Section {
	unsigned int textureIndex;
	std::vector<Vertice> vertices;
	std::vector<unsigned int> indices;
	unsigned int GetVerticeByteWidth(void) const;
	unsigned int GetIndiceByteWidth(void) const;
};

class ModelBase : public AssetBase
{
public:
	std::vector<Section> sections;

public:
	virtual bool Load(const std::string& path) override;

private:
	bool LoadWithAssimp(const std::string& path);
};