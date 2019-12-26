#ifndef __DOTTH_RENDERER_HPP__
#define __DOTTH_RENDERER_HPP__

#include "dotth.hpp"
#include "render_queue.hpp"

namespace dotth {    
    class renderer : public utility::singleton<renderer> {
    public:
        void init_gl(int argc, char** argv);
		void flush(void);
	public:
		void push_back(dotth::render::command::inherit* inherit);
		void process(const dotth::render::draw_type& type);
	private:
        std::map<dotth::render::draw_type, dotth::render_queue> _queue;
		unsigned int _drawing_object_cnt = 0;
    };
};

#endif // __DOTTH_RENDERER_HPP__
