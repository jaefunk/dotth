#pragma once

#include "dotth.h"

struct vertice {
	Vector3F position;
	Vector3F normal;
	Vector3F tangent;
	Vector3F bitangent;
	Vector2F textureCoord;
	Vector4F color;
};

struct section {
	std::string name;
	unsigned int textureIndex;
	std::vector<vertice> vertices;
	std::vector<unsigned int> indices;
	unsigned int GetVerticeByteWidth(void)
	{
		return static_cast<unsigned int>(sizeof(decltype(vertices)::value_type) * vertices.size());
	}
	unsigned int GetIndiceByteWidth(void)
	{
		return static_cast<unsigned int>(sizeof(decltype(indices)::value_type) * indices.size());
	}
};

struct texture {
	std::string name;
	unsigned int width;
	unsigned int height;
	std::vector<Color4F> pixels;
};

class model 
{
protected:
	std::string name;
	std::vector<section> sections;
	std::vector<texture> textures;

public:
	bool LoadWithAssimp(const std::string& path);
};