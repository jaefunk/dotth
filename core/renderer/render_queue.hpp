#ifndef __DOTTH_RENDER_QUEUE_HPP__
#define __DOTTH_RENDER_QUEUE_HPP__

#include "dotth.hpp"
#include "renderer/draw_command.hpp"

namespace dotth {
	class render_queue {
	public:
		void push_back(class drawable* drawable);
		void push_back(class render::command::inherit* command);
		void clear(void);
		void process(void) const;
	private:
		std::vector<class drawable*> drawables;
		std::vector<render::command::inherit*> commands;
	};
};

#endif // __DOTTH_RENDER_QUEUE_HPP__
