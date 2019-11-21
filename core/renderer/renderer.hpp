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

#include "dotth.hpp"
#include "render_queue.hpp"

namespace dotth {
	namespace gl_callback {
        void display(void);
        void reshape(int width, int height);
	};
    
    class renderer : public utility::singleton<renderer> {
    public:
        void init_gl(int argc, char** argv);
		void clear_all_queue(void);
	public:
		void push_back(class drawable* drawable);
		const std::shared_ptr<dotth::render_queue> find_render_queue(const dotth::render::draw_type& type);
	private:
        std::map<dotth::render::draw_type, std::shared_ptr<dotth::render_queue>> queue;
    };
};

#endif // __DOTTH_RENDERER_HPP__
