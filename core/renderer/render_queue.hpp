#ifndef __DOTTH_RENDER_QUEUE_HPP__
#define __DOTTH_RENDER_QUEUE_HPP__

#include "dotth.hpp"

namespace dotth {
	class render_queue {
	public:
		void push_back(class drawable* drawable);
		void clear(void);
		void process(void) const;
	private:
		std::vector<class drawable*> drawables;
	};
};

#endif // __DOTTH_RENDER_QUEUE_HPP__
