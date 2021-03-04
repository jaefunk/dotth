
#pragma once

#include "Base.h"

template <typename Ty>
class SingleInstance : public Base
{
public:
	static Ty* Instance(void)
	{
		static Ty v;
		return &v;
	}
};