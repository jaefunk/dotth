#pragma once

#include "framework/node.h"
#include "framework/component.h"

class object : public node<object>
{
private:
	std::string _name;
	std::list<std::shared_ptr<component>> _components;

public:
	void set_name(const char* name)
	{
		_name = name;
	}
public:
	template <class ty = object>
	std::shared_ptr<ty> find_by_name(const char* name)
	{
		auto finded = find_by_func([name](std::shared_ptr<object> child) {
			return child->_name.c_str() == name;
		});
		return std::dynamic_pointer_cast<ty>(finded);
	}

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
};