#include "Framework/Base.h"

Base::Base(void)
{
	static std::atomic<unsigned int> s;
	_Serial = s.fetch_add(1);
	_Name = std::to_string(_Serial);
}

const unsigned int & Base::Serial(void) const
{
	return _Serial;
}

void Base::SetName(const std::string & Name)
{
	_Name = Name;
}

const std::string & Base::GetName(void)
{
	return _Name;
}
