#ifndef __DOTTH_PRIMITIVE_HPP__
#define __DOTTH_PRIMITIVE_HPP__

#include "base/drawable.hpp"

namespace dotth {
	class rectangle : public dotth::drawable
	{
	public:
		rectangle(void) : dotth::drawable(dotth::render::transform_type::orthographic) {}
	public:
		virtual void on_init(void) override;
		virtual void on_update(const float& delta) override;
	public:
		void set_color(const render::rgba& _color);
		virtual void on_pre_render(void) override {};
		virtual void on_render(void) override;
		virtual void on_post_render(void) override {};
	};

	class cube : public dotth::drawable
	{
	public:
		cube(void) : dotth::drawable(dotth::render::transform_type::perspective) {}
	public:
		virtual void on_init(void) override;
		virtual void on_update(const float& delta) override;
		virtual void on_pre_render(void) override;
		virtual void on_render(void) override;
		virtual void on_post_render(void) override;

		unsigned int framebuffer = 0;
		unsigned int texturebuffer = 0;
	};
};

#endif // __DOTTH_PRIMITIVE_HPP__
