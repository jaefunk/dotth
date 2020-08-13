
#pragma once

#include "Framework/Object.h"
#include "Components/CubeComponent.h"

class sample_object : public Object
{
public:
	sample_object(void)
	{
		AttachComponent(std::make_shared<CubeComponent>());
	}
};