#ifndef __DOTTH_RENDER_QUEUE_HPP__
#define __DOTTH_RENDER_QUEUE_HPP__

#include "dotth.hpp"
#include "draw_command.hpp"

namespace dotth {
	class render_queue {
	public:
		void push_back(dotth::render::command::inherit* command);
		void clear(void);
		void process(void) const;
	private:
		std::vector<dotth::render::command::inherit*> commands;
	};
};

#endif // __DOTTH_RENDER_QUEUE_HPP__
