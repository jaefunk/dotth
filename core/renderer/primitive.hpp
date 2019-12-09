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
		// anchor left = -1.f top = 1.f right = 1.f bottom = -1.f
		// size
		void set_size(const int& width, const int& height);
		void set_anchor(const float& x, const float& y);
		void set_color(const render::rgba& _color);
	};
};

#endif // __DOTTH_PRIMITIVE_HPP__
