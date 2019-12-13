#ifndef __DOTTH_DRAWABLE_HPP__
#define __DOTTH_DRAWABLE_HPP__

#include "object.hpp"
#include "renderer/draw_command.hpp"

namespace dotth {
	using namespace render::command;
	class drawable : public object
	{
	public:
		drawable(const dotth::render::transform_type& _type);
		virtual ~drawable(void);
		
		template <typename ty>
		void assign_command(void)
		{
			_command = new ty;
		}

		template <typename ty = transform>
		ty* trans(void)
		{
			return (ty*)_trans;
		}

		template <typename ty = dotth::render::command::inherit>
		ty* command(void)
		{
			return (ty*)_command;
		}
	};
};

#endif // __DOTTH_DRAWABLE_HPP__
