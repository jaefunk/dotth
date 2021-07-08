#pragma once

#include "dotth.h"

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

struct texture {
	std::string name;
	unsigned int width;
	unsigned int height;
	std::vector<Color4F> pixels;

	bool Load(const std::string& path);
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