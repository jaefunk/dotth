#include "framework/base.h"

base::base(void)
{
	static std::atomic<int> s;
	_serial = s.fetch_add(1);
}

const int & base::serial(void) const
{
	return _serial;
}