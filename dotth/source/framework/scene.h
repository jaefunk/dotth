#pragma once

#include "framework/object.h"
#include "utility/single_instance.h"
#include "graphics/camera.h"

class scene;
class scenario : public single_instance<scenario>
{
private:
	bool _scene_changed = false;
	json _scene_data;
	std::stack<std::string> _stack;
	std::unordered_map<std::string, std::function<std::shared_ptr<scene>(void)>> _signed_scene;
	std::shared_ptr<scene> _current;
	void apply_new_scene(void);

public:
	void push(std::string key, json data = json());
	void pop(json data = json());
	void loop(void);

public:
	template <typename ty, typename = typename std::enable_if<std::is_base_of<scene, ty>::value, ty>::type>
	void assign_scene(const std::string& key)
	{
		_signed_scene.insert({ key, []() { return std::make_shared<ty>(); } });
	}
};

class scene : public object
{
protected:
	bool loadview(const std::string& path);
};