#include "Framework/Component.h"

std::shared_ptr<Object> Component::GetOwner(void)
{
	return _Owner;
}
