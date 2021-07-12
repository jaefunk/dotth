#pragma once

#include "AssetBase.h"

struct vertice {
	Vector3F position;
	Vector3F normal;
	Vector2F textureCoord;
	Vector3F tangent;
	Vector3F bitangent;
	Vector4F color;
};

struct section {
	std::string name;
	unsigned int textureIndex;
	std::vector<vertice> vertices;
	std::vector<unsigned int> indices;
	unsigned int GetVerticeByteWidth(void) const;
	unsigned int GetIndiceByteWidth(void) const;
};

class model : public AssetBase
{
public:
	std::string name;
	std::vector<section> sections;

public:
	virtual bool Load(const ASSET_TYPE& type, const std::string& path) override
	{
		if (type == ASSET_TYPE::FBX)
			return LoadWithAssimp(path);
		return false;
	}

private:
	bool LoadWithAssimp(const std::string& path);
};