
#include "object.h"
#include "framework/component.h"

object::object(void)
{
	_name = std::to_string(serial());
}

void object::set_name(const std::string & name)
{
	_name = name;
}

const std::string & object::get_name(void)
{
	return _name;
}

void object::init(void)
{
	on_init();
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

void object::add_component(std::string name, std::shared_ptr<component> target)
{
	if (_components.end() != std::find(_components.begin(), _components.end(), target))
		return;
	_components.push_back(target);
}
