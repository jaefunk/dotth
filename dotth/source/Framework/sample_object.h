
#pragma once

#include "Framework/Object.h"
#include "Graphics/model.h"
#include "Graphics/shader.h"

class sample_object : public Object
{
public:
	sample_object(void)
	{
		AttachComponent(std::make_shared<model>());
		AttachComponent(std::make_shared<sdr2222>());
	}
};