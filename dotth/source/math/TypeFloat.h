
#pragma once

struct Float2 {
	union {
		struct { float _[2]; };
		struct { float x; float y; };
		struct { float a; float b; };
	};
};

struct Float3 {
	union {
		struct { float _[3]; };
		struct { float x; float y; float z; };
		struct { float r; float g; float b; };
		struct { float a; float b; float c; };
	};
};

struct Float4 {
	union {
		struct { float _[4]; };
		struct { float x; float y; float z; float w; };
		struct { float r; float g; float b; float a; };
		struct { float a; float b; float c; float d; };
	};
};