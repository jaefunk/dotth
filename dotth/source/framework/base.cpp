#include "framework/base.h"

base::base(void)
{
	static std::atomic<unsigned int> s;
	_serial = s.fetch_add(1);
	_name = std::to_string(_serial);
}

const unsigned int & base::serial(void) const
{
	return _serial;
}

void base::name(const std::string & name)
{
	_name = name;
}

const std::string & base::name(void)
{
	return _name;
}
