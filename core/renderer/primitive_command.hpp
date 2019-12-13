#ifndef __DOTTH_PRIMITIVE_COMMAND_HPP__
#define __DOTTH_PRIMITIVE_COMMAND_HPP__

#include "draw_command.hpp"

namespace dotth {
	namespace render {
		namespace command {
			struct primitive_orthographic : public render::command::inherit {
				std::vector<render::xyz> v;
				std::vector<render::rgba> c;
				std::vector<unsigned int> i;
				virtual void draw(void);
			};
			struct primitive_perspective : public render::command::inherit {
				std::vector<render::xyz> v;
				std::vector<render::rgba> c;
				std::vector<unsigned int> i;
				virtual void draw(void);
			};
		}
	}
};

#endif // __DOTTH_PRIMITIVE_COMMAND_HPP__
