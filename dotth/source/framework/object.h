#pragma once

#include "framework/node.h"
#include "framework/component.h"

class object : public node<object>
{
	friend component;
public:
	void init(void);
	void update(void);
	void render(void);
	void destroy(void);

protected:
	virtual void on_init(void) {};
	virtual void on_update(void) {};
	virtual void on_render(void) {};
	virtual void on_destroy(void) {};

public:
	template <class ty = object>
	std::shared_ptr<ty> find_by_serial(unsigned int serial)
	{
		auto finded = find_by_func([serial](std::shared_ptr<object> child) {
			return child->serial() == serial;
		});
		return std::dynamic_pointer_cast<ty>(finded);
	}
	template <class ty = object>
	std::shared_ptr<ty> find_by_name(const std::string& name)
	{
		auto finded = find_by_func([name](std::shared_ptr<object> child) {
			return child->name() == name;
		});
		return std::dynamic_pointer_cast<ty>(finded);
	}

private:
	std::list<std::shared_ptr<component>> _components;
public:
	void attach_component(std::shared_ptr<component> target, std::string name = std::string())
	{
		if (_components.end() != std::find(_components.begin(), _components.end(), target))
			return;
		target->_owner = this->shared_from_this();
		_components.push_back(target);
	}

	void detach_component(std::shared_ptr<component> target)
	{
		target->_owner = nullptr;
		_components.remove(target);
	}

	template <typename ty>
	std::shared_ptr<ty> find_component(void)
	{
		for (const auto& comp : _components)
		{
			if (auto casted = std::dynamic_pointer_cast<ty>(comp))
				return casted;
		}
		return nullptr;
	}
};
