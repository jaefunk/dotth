#ifndef __DOTTH_INPUT_HPP__
#define __DOTTH_INPUT_HPP__

#include "dotth.hpp"

namespace dotth {
	struct mouse {
		vector2 pos;
		int button = 0;
		int state = 0;
	};
	struct keyboard {
		unsigned char key = 0;
	};
	class input : public dotth::utility::singleton<input> {
		std::list<mouse> _mouse_input_list;
		std::list<keyboard> _keyboard_input_list;
	public:
		void flush(void)
		{
			printf("mouse: %d keyboard: %d\n", _mouse_input_list.size(), _keyboard_input_list.size());
			_mouse_input_list.clear();
			_keyboard_input_list.clear();
		}
		void push_mouse_input(int x, int y, int button, int state)
		{
			mouse m;
			m.pos = { static_cast<float>(x), static_cast<float>(y) };
			m.button = button;
			m.state = state;
			_mouse_input_list.push_back(m);
		}
		void push_mouse_move(int x, int y)
		{
		}
		void push_keyboard_input(unsigned char key)
		{
			keyboard k;
			k.key = key;
			_keyboard_input_list.push_back(k);
		}
	};
};

#endif // __DOTTH_COMPONENT_HPP__
