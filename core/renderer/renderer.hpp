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

#ifndef __DOTTH_RENDERER_HPP__
#define __DOTTH_RENDERER_HPP__

#include <algorithm>
#include <vector>
#include <map>

#include "base/utility.hpp"

namespace dotth {
	namespace gl_callback {
        void display(void);
        void reshape(int width, int height);
	};

    enum class render_command_type {
        unknown,
        triangles,
    };
    class render_command {
    public:
        render_command(render_command_type type) : _type(type) {}
        const render_command_type type(void) { return _type; }
    protected:
        render_command_type _type = render_command_type::unknown;
    };

	struct xyzrgba {
		float x, y, z, r, g, b, a;
		void pos(float x, float y, float z)
		{
			this->x = x;
			this->y = y;
			this->z = z;
		}
		void color(float r, float g, float b, float a)
		{
			this->r = r;
			this->g = g;
			this->b = b;
			this->a = a;
		}
	};
	struct triangles {
		std::vector<xyzrgba> vertexs;
	};
	struct triangle_command : public render_command {
		triangle_command(void) : render_command(render_command_type::triangles) {}
		triangles _triangle;
		void init(const triangles& triangle) {
			_triangle = triangle;
		}
	};

    enum render_queue_type {
        perspective,
        count = 1,
    };
    class render_queue {
    public:
        void push_back(render_command* command) {
            commands.push_back(command);
        }
        void clear(void) {
            commands.clear();
        }
		void process(void);
    private:
        std::vector<render_command*> commands;
    };
    
    class renderer : public utility::singleton<renderer> {
    public:
        void init_gl(int argc, char** argv);
	public:
		void push(render_command* command)
		{
			switch (command->type()) {
				case render_command_type::triangles: 
					queue[render_queue_type::perspective].push_back(command);
				break;
			}
		}
	
		const render_queue& find_render_queue(const render_queue_type& type) {
			return queue[type];
		}
	private:
        std::map<render_queue_type, render_queue> queue;
    };
};

#endif // __DOTTH_RENDERER_HPP__
