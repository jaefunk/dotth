
#include "object.h"

void dotth::object::init(void)
{
	_drawable.init_triangle();
	on_init();
	foreach([](std::shared_ptr<dotth::object> child) {
		child->init();
	});
}

void dotth::object::update(void)
{
	on_update();
	foreach([](std::shared_ptr<dotth::object> child) {
		child->update();
	});
}

void dotth::object::render(void)
{
	_drawable.draw();
	on_render();
	foreach([](std::shared_ptr<dotth::object> child) {
		child->render();
	});
}
