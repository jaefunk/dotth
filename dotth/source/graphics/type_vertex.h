
#pragma once

#include <DirectXMath.h>

namespace vertex
{
	struct position_color
	{
		XMFLOAT3 position;		// x, y, z
		XMFLOAT4 color;			// r, g, b, a
	};

	struct position_color_normal
	{
		XMFLOAT3 position;		// x, y, z
		XMFLOAT4 color;			// r, g, b, a
		XMFLOAT3 normal;		// x, y, z
	};
}