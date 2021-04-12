#pragma once

#include "dotth.h"
#include "Math/Math.h"

struct Vertex
{
	Vector3F Position;
	Vector3F Normal;
	Vector2F UV;
	Vector3F Color;
};

class Mesh
{
private:
	std::vector<Vertex> Vertices;
	std::vector<uint32_t> Indices;

	void Clear(void) {

	}
	bool IsValid(void) const {
		return true;
	}
};