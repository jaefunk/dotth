#include "scene.h"

bool scene::loadview(const std::string& path) 
{
	return true;
}

void scenario::push(std::string key, json data)
{
	_stack.push(key);
	_scene_changed = true;
	_scene_data = data;
}

void scenario::pop(json data)
{
	if (_stack.size() <= 1)
		return;
	_stack.pop();
	_scene_changed = true;
	_scene_data = data;
}

void scenario::apply_new_scene(void)
{
	if (_stack.empty() == true)
		return;
	if (_scene_changed == false)
		return;
	_scene_changed = false;
	auto iterator = _signed_scene.find(_stack.top());
	if (iterator == std::end(_signed_scene))
		return;
	_current = iterator->second();
	_current->init();
	_scene_data = json();
}

void scenario::loop(void)
{
	apply_new_scene();
	if (_current == nullptr)
		return;
	_current->update();
	camera::get()->sync();
	_current->render();
}
