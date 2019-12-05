#ifndef __DOTTH_APPLICATION_HPP__
#define __DOTTH_APPLICATION_HPP__

#include "dotth.hpp"

namespace dotth {
    class application : public utility::singleton<application> {
	private:
		std::thread render_thread;
		std::thread refresh_thread;
    public:
		void init(int argc, char ** argv);
		int process(void);
    };
};

#endif // __DOTTH_APPLICATION_HPP__
