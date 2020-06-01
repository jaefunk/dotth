
#pragma once

#include <DirectXMath.h>

namespace dotth
{
	namespace vertex
	{
		struct position_color
		{
			XMFLOAT3 position;		// x, y, z
			XMFLOAT4 color;			// r, g, b, a
		};
		using pc = position_color;

		struct position_color_normal
		{
			XMFLOAT3 position;		// x, y, z
			XMFLOAT4 color;			// r, g, b, a
			XMFLOAT3 normal;		// x, y, z
		};
		using pcn = position_color_normal;
	}
}