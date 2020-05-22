#pragma once

#include "node.h"

namespace dotth {
	
	class object : public node<object>
	{
	public:
		virtual void init(void) final;
		virtual void update(void) final;

	protected:
		virtual void on_init(void) {};
		virtual void on_update(const float& delta) {};
	};
};