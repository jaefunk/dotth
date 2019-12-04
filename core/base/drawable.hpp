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

#ifndef __DOTTH_DRAWABLE_HPP__
#define __DOTTH_DRAWABLE_HPP__


#include "object.hpp"
#include "renderer/draw_command.hpp"
#include "renderer/shader.hpp"

namespace dotth {
	class drawable : public object
	{
	public:
		dotth::render::draw_type _draw_type = dotth::render::draw_type::none;
	protected:
        std::shared_ptr<class shader> _shader;
	public:
		drawable(const dotth::render::draw_type _draw_type) : _draw_type(_draw_type) {}
		const dotth::render::draw_type draw_type(void) { return _draw_type; }
		void set_shader(const char* key);
	public:
		virtual void on_push_render_queue(void) final;
		virtual void draw(const int flags) = 0;
	};
};

#endif // __DOTTH_DRAWABLE_HPP__
