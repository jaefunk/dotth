#include "framework/base.h"
#include "utility/utility.h"

base::base(void)
{
	static std::atomic<int> s;
	static utility::timer t;
	_serial = s.fetch_add(1);
	_birth = t.time_since_epoch();
}

const int & base::serial(void) const
{
	return _serial;
}

const std::time_t & base::birth(void) const
{
	return _birth;
}
