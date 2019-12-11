#include "object.hpp"

void dotth::object::set_timescale(const float & scale) {
	_timescale = scale;
}

const float & dotth::object::local_timescale(void) {
	return _timescale;
}

const float dotth::object::world_timescale(void) {
	if (is_root())
		return _timescale;
	return _timescale * parent()->world_timescale();
}

void dotth::object::update(void)
{
	if (flags.alive == false)
	{
		independence();
		return;
	}
	if (flags.active == false)
	{
		return;
	}
	
	transform2d parent_transform2d;
	transform3d parent_transform3d;
	if (is_root() == false)
	{
		parent_transform3d = parent<object>()->trans3d;
		parent_transform2d = parent<object>()->trans2d;
	}
	trans3d.sync(parent_transform3d);		
	trans2d.sync(parent_transform2d);

	on_update(utility::timer::instance()->delta() * world_timescale());
	foreach<object>([](std::shared_ptr<object> obj) { obj->update(); });
}

void dotth::object::push_render_queue(void)
{
	if (flags.visible == false)
	{
		return;
	}
	on_push_render_queue();
	foreach<object>([](std::shared_ptr<object> obj) { obj->push_render_queue(); });
}
