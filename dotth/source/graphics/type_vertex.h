
#pragma once

#include "../math/type_float.h"

namespace dotth
{
	namespace vertex
	{
		struct position_color
		{
			float3 position;	// x, y, z
			float4 color;		// r, g, b, a
		};
		using pc = position_color;

		struct position_color_normal
		{
			float3 position;	// x, y, z
			float4 color;		// r, g, b, a
			float3 normal;		// x, y, z
		};
		using pcn = position_color_normal;
	}
}