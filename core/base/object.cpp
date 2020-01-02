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
	if (_flags.alive == false)
	{
		independence();
		return;
	}
	if (_flags.active == false)
		return;

	_trans.sync(is_root() == false ? &parent<object>()->_trans : nullptr);
	if (_command != nullptr)
		memcpy(_command->_model, _trans.result(), matrix4::matrix_size);
	on_update(utility::timer::instance()->delta() * world_timescale());
	foreach<object>([](std::shared_ptr<object> obj) { 
		obj->update(); 
	});
}

void dotth::object::render(void)
{
	if (_flags.visible == false)
		return;
	on_pre_render();
	foreach<object>([](std::shared_ptr<object> obj) { obj->render(); });
	on_render();
	
	on_post_render();
}
