#pragma once

#include "framework/base.h"

class object;
class component : public base
{
	friend object;
private:
	std::shared_ptr<object> _owner;

public:
	std::shared_ptr<object> owner(void)
	{
		return _owner;
	}

public:
	virtual void pre_init(void) {};
	virtual void pre_update(void) {};
	virtual void pre_render(void) {};
	virtual void pre_destroy(void) {};

	virtual void post_init(void) {};
	virtual void post_update(void) {};
	virtual void post_render(void) {};
	virtual void post_destroy(void) {};
};
