
#pragma once

#include "Framework/Base.h"

template <typename ty>
class single_instance : public Base
{
public:
	static ty* get(void)
	{
		static ty v;
		return &v;
	}
};