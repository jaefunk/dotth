
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
	std::for_each(_components.begin(), _components.end(), [](decltype(_components)::value_type component) {
		component->pre_update();
	});
	on_update();
	std::for_each(_components.begin(), _components.end(), [](decltype(_components)::value_type component) {
		component->post_update();
	});	
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

void object::destroy(void)
{
	on_destroy();
	foreach([](std::shared_ptr<object> child) {
		child->on_destroy();
	});
}
