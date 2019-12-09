#ifndef __DOTTH_DRAWABLE_HPP__
#define __DOTTH_DRAWABLE_HPP__

#include "object.hpp"
#include "renderer/draw_command.hpp"

namespace dotth {
	class drawable : public object
	{
	protected:
		std::shared_ptr<dotth::render::command::inherit> _command;
	public:
		virtual void on_push_render_queue(void) final;
	};
};

#endif // __DOTTH_DRAWABLE_HPP__
