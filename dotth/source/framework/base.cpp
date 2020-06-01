#include "base.h"
#include "utility/utility.h"

dotth::base::base(void)
{
	static std::atomic<int> s;
	static utility::timer t;
	_serial = s.fetch_add(1);
	_birth = t.time_since_epoch();
}

const int & dotth::base::serial(void) const
{
	return _serial;
}

const std::time_t & dotth::base::birth(void) const
{
	return _birth;
}
