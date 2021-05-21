#pragma once

#include "dotth.h"
#include "Math/Math.h"

struct MatrixBuffer
{
	XMMATRIX World;
	XMMATRIX View;
	XMMATRIX Projection;
};

struct Vertex
{
	Vector3F Position;
	//Vector3F Normal;
	//Vector2F UV;
	Color4F Color;
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

	void Clear(void) {

	}
	bool IsValid(void) const {
		return true;
	}
};