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

	transform* _parent_trans = nullptr;
	if (is_root() == false)
		_parent_trans = parent<object>()->trans.get();
	if (trans != nullptr)
		trans->sync(_parent_trans);

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
