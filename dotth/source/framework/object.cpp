
#include "object.h"

void object::init(void)
{
	on_init();
	foreach([](std::shared_ptr<object> child) {
		child->init();
	});
}

void object::update(void)
{
	on_update();
	foreach([](std::shared_ptr<object> child) {
		child->update();
	});
}

void object::render(void)
{
	on_render();
	foreach([](std::shared_ptr<object> child) {
		child->render();
	});
}
