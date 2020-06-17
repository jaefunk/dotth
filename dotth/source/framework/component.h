#pragma once

#include "framework/base.h"

class component : public base
{
private:
	// owner
	// name
public:
	virtual void pre_update(void) {};
	virtual void pre_render(void) {};
	virtual void pre_destroy(void) {};
	virtual void post_update(void) {};
	virtual void post_render(void) {};
	virtual void post_destroy(void) {};
};
