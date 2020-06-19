#pragma once

#include "framework/node.h"

class object : public node<object>
{
private:
	std::string _name;
	std::list<std::shared_ptr<class component>> _components;

public:
	object(void);
	void set_name(const std::string& name);
	const std::string& get_name(void);

public:
	void init(void);
	void update(void);
	void render(void);
	void destroy(void);

	void add_component(std::string name, std::shared_ptr<class component> target);

protected:
	virtual void on_init(void) {};
	virtual void on_update(void) {};
	virtual void on_render(void) {};
	virtual void on_destroy(void) {};

public:
	template <class ty = object>
	std::shared_ptr<ty> find_by_name(const std::string& name)
	{
		auto finded = find_by_func([name](std::shared_ptr<object> child) {
			return child->_name == name;
		});
		return std::dynamic_pointer_cast<ty>(finded);
	}
};