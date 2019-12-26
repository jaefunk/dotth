#ifndef __DOTTH_GL_GLOBAL_CALLBACK_HPP__
#define __DOTTH_GL_GLOBAL_CALLBACK_HPP__

#include "dotth.hpp"

namespace dotth {
	namespace gl_global_callback {
		void display(void);
		void reshape(int width, int height);

		void timer(int value);
		void keyboard(unsigned char key, int x, int y);
		void mouse(int button, int state, int x, int y);		
		void motion(int x, int y);
	};
};

#endif // __DOTTH_GL_GLOBAL_CALLBACK_HPP__
