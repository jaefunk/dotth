/*
Licensed under the MIT License <http://opensource.org/licenses/MIT>.
Copyright (c) 2019 jaefunk <https://github.com/jaefunk/dotth>.

Permission is hereby  granted, free of charge, to any  person obtaining a copy
of this software and associated  documentation files (the "Software"), to deal
in the Software  without restriction, including without  limitation the rights
to  use, copy,  modify, merge,  publish, distribute,  sublicense, and/or  sell
copies  of  the Software,  and  to  permit persons  to  whom  the Software  is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE  IS PROVIDED "AS  IS", WITHOUT WARRANTY  OF ANY KIND,  EXPRESS OR
IMPLIED,  INCLUDING BUT  NOT  LIMITED TO  THE  WARRANTIES OF  MERCHANTABILITY,
FITNESS FOR  A PARTICULAR PURPOSE AND  NONINFRINGEMENT. IN NO EVENT  SHALL THE
AUTHORS  OR COPYRIGHT  HOLDERS  BE  LIABLE FOR  ANY  CLAIM,  DAMAGES OR  OTHER
LIABILITY, WHETHER IN AN ACTION OF  CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE  OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef __DOTTH_RENDER_COMMAND_HPP__
#define __DOTTH_RENDER_COMMAND_HPP__

#include <vector>

namespace dotth {
	struct xyz {
		float x, y, z;
		xyz(void) {};
		xyz(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
	};
	struct uv {
		float u, v;
		uv(void) {};
		uv(float _u, float _v) : u(_u), v(_v) {}
	};
	struct rgba {
		float r, g, b, a;
		rgba(void) { r = 1.f; g = 1.f; b = 1.f; a = 1.f; };
		rgba(float _r, float _g, float _b, float _a) : r(_r), g(_g), b(_b), a(_a) {}
	};
	struct v3f_c4b {
		xyz v;
		rgba c;
	};

	struct polygon {
		std::vector<xyz> v;
		std::vector<rgba> c;
		std::vector<uv> u;
		std::vector<xyz> n;
		std::vector<unsigned int> i;
	};

	enum render_queue_type {
		perspective,
		count = 1,
	};

	enum class render_command_type {
		unknown,
		polygons,
	};

	class render_command {
	public:
		render_command(render_command_type type) : _type(type) {}
		const render_command_type type(void) { return _type; }
	protected:
		render_command_type _type = render_command_type::unknown;
	};

	struct polygon_command : public render_command {
		polygon_command(void) : render_command(render_command_type::polygons) {}
		polygon _triangle;
		void init(const polygon& triangle) {
			_triangle = triangle;
		}
	};
};

#endif // __DOTTH_RENDER_COMMAND_HPP__
