
#include "ObjectBase.h"

void ObjectBase::AddFlag(std::string flag)
{
	if (Flags.find(flag) == Flags.end())
		return;
	Flags.insert(flag);
}

bool ObjectBase::HasFlag(std::string flag)
{
	return Flags.find(flag) != Flags.end();
}

void ObjectBase::RemoveFlag(std::string flag)
{
	Flags.erase(flag);
}

void ObjectBase::ClearFlag(void)
{
	Flags.clear();
}
