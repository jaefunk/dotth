#include "base.hpp"

dotth::base::base(void) 
{
	static std::atomic<int> s;
	_serial = s.fetch_add(1);
	_birth = dotth::utility::timer::instance()->time_since_epoch();
}

const int & dotth::base::serial(void) const 
{
	return _serial;
}

const std::time_t & dotth::base::birth(void) const 
{
	return _birth;
}
