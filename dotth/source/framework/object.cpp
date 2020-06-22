
#include "object.h"

void object::init(void)
{
	std::for_each(_components.begin(), _components.end(), [](std::shared_ptr<component> component) {
		component->pre_init();
	});
	on_init();
	std::for_each(_components.begin(), _components.end(), [](std::shared_ptr<component> component) {
		component->post_init();
	});
	foreach([](std::shared_ptr<object> child) {
		child->init();
	});
}

void object::update(void)
{
	std::for_each(_components.begin(), _components.end(), [](std::shared_ptr<component> component) {
		component->pre_update();
	});
	on_update();
	std::for_each(_components.begin(), _components.end(), [](std::shared_ptr<component> component) {
		component->post_update();
	});
	foreach([](std::shared_ptr<object> child) {
		child->update();
	});
}

void object::render(void)
{
	std::for_each(_components.begin(), _components.end(), [](std::shared_ptr<component> component) {
		component->pre_render();
	});
	on_render();
	std::for_each(_components.begin(), _components.end(), [](std::shared_ptr<component> component) {
		component->post_render();
	});
	foreach([](std::shared_ptr<object> child) {
		child->render();
	});
}

void object::destroy(void)
{
	leave();
	std::for_each(_components.begin(), _components.end(), [](std::shared_ptr<component> component) {
		component->pre_destroy();
	});
	on_destroy();
	std::for_each(_components.begin(), _components.end(), [](std::shared_ptr<component> component) {
		component->post_destroy();
	});
	foreach([](std::shared_ptr<object> child) {
		child->destroy();
	});
}
