#ifndef __DOTTH_PRIMITIVE_HPP__
#define __DOTTH_PRIMITIVE_HPP__

#include "base/drawable.hpp"

namespace dotth {
	class rectangle : public dotth::drawable
	{
	public:
		virtual void init(void) override;
		virtual void on_update(const float& delta) override;

	public:
		void set_color(const render::rgba& _color);
	};
};

#endif // __DOTTH_PRIMITIVE_HPP__
