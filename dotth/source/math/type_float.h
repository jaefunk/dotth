
#pragma once

namespace dotth 
{
	struct float2 {
		union { 
			struct { float _[2]; };
			struct { float x, y; };
			struct { float a, b; };
		};
	};

	struct float3 {
		union {
			struct { float _[3]; };
			struct { float x, y, z; };
			struct { float r, g, b; };
			struct { float a, b, c; };
		};
	};

	struct float4 {
		union {
			struct { float _[4]; };
			struct { float x, y, z, w; };
			struct { float r, g, b, a; };
			struct { float a, b, c, d; };
		};
	};
};
