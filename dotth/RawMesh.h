#pragma once

#include "dotth.h"
#include "Math/Math.h"

enum
{
	MAX_TEXTURE_COORDS = 8,
};

struct RawMesh
{
	std::vector<Vector3F> Vertices;
	std::vector<uint32_t> Indices;
	std::vector<Vector3F> Normals;
	std::vector<uint32_t> Colors;
	std::vector<Float2> TexCoords[MAX_TEXTURE_COORDS];
};