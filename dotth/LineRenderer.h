#pragma once

#include "SingleInstance.h"
#include "Renderable.h"

struct Line {
	dotth::vector3 from;
	dotth::vector3 to;
	dotth::vector4 color;
	float duration;
};

class LineRenderer : SingleInstance<LineRenderer>
{
public:
	static void Update(void)
	{

	}
	static void Draw(void)
	{

	}
};