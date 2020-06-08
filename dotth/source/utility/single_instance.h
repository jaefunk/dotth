
#pragma once

#include "framework/base.h"

template <typename ty>
class single_instance : public base
{
public:
	static ty* get(void)
	{
		static ty v;
		return &v;
	}
};