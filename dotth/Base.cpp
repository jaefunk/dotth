#include "Base.h"

Base::Base(void)
{
	static std::atomic<unsigned int> s;
	Serial = s.fetch_add(1);
	Name = std::to_string(Serial);
}

Base::~Base(void)
{
}

unsigned int Base::GetSerial(void) const
{
	return Serial;
}

std::string Base::GetName(void) const
{
	return Name;
}

void Base::Rename(const std::string& name)
{
	Name = name;
}

