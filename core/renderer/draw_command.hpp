#ifndef __DOTTH_DRAW_COMMAND_HPP__
#define __DOTTH_DRAW_COMMAND_HPP__

#include "dotth.hpp"

namespace dotth {
	namespace render {
		enum class draw_type {
			none,
			perspective,
			orthographic,
		};
		struct xyz {
			float x, y, z;
			xyz(void) { x = 0.f, y = 0.f, z = 0.f; };
			xyz(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
		};
		struct uv {
			float u, v;
			uv(void) { u = 0.f; v = 0.f; };
			uv(float _u, float _v) : u(_u), v(_v) {}
		};
		struct rgba {
			float r, g, b, a;
			rgba(void) { r = 1.f; g = 1.f; b = 1.f; a = 1.f; };
			rgba(float _r, float _g, float _b, float _a) : r(_r), g(_g), b(_b), a(_a) {}
		};
		namespace command {
			struct inherit {
				draw_type type = draw_type::none;
				float model[16];
				float view[16];
				float proj[16];
				unsigned int program;
				virtual void draw(void) = 0;
			};
		}
	}
};

#endif // __DOTTH_DRAW_COMMAND_HPP__
