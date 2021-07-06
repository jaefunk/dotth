#pragma once

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
#include "dotth.h"

struct mesh {
	std::string name;
	unsigned int textureIndex;
	std::vector<Vector3F> vertices;
	std::vector<Vector3F> normals;
	std::vector<Vector2F> textureCoords;
	std::vector<unsigned int> indices;
};

struct texture {
	std::string name;
	unsigned int width;
	unsigned int height;
	std::vector<Color4F> pixels;
};

struct model {
	std::string name;
	std::vector<mesh> meshs;
	std::vector<texture> textures;
};

struct Vertex
{
	Vector3F Position;
	Color4F Color;
	Vector3F Normal;
	Vector2F UV;
	//static constexpr std::size_t Size(void)
	//{
	//	return sizeof(Vertex);
	//}
	Vertex(void)
	{
	}
	Vertex(const Vertex& v)
	{
		Position = v.Position;
		Color = v.Color;
	}
	Vertex(Vector3F pos, Color4F color)
	{
		Position = pos;
		Color = color;
	}
};

class Mesh
{
public:
	Matrix Matrix;
	std::vector<Vertex> Vertices;
	std::vector<uint32_t> Indices;
};

class asset3d
{
};