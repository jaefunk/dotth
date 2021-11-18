#include "Base.h"

Base::Base(void)
{
	static std::atomic<unsigned int> s;
	serial = s.fetch_add(1);
	name = std::to_string(serial);
}

unsigned int Base::GetSerial(void) const
{
	return serial;
}

std::string Base::GetName(void) const
{
	return name;
}

void Base::Rename(const std::string& newName)
{
	name = newName;
}

