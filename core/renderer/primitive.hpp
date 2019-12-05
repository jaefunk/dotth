#ifndef __DOTTH_PRIMITIVE_HPP__
#define __DOTTH_PRIMITIVE_HPP__

#include "base/drawable.hpp"
#include "primitive_command.hpp"

namespace dotth {
	class rectangle : public dotth::drawable
	{
	public:
		rectangle(void);
		virtual void init(void) override;
		void set_color(const render::rgba& _color);
	protected:
		render::command::primitive _vertex;
	private:		
		virtual void on_update(const float& delta) override;
		virtual void draw(const int flags) override;		
	};
};

#endif // __DOTTH_PRIMITIVE_HPP__
