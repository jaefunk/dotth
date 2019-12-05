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
