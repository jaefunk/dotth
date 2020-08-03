
#pragma once

#include "Framework/Object.h"
#include "graphics/camera.h"
#include "graphics/model.h"
#include "graphics/shader.h"

class sample_object : public Object
{
private:
	std::shared_ptr<model> _model;
	std::shared_ptr<sdr2222> _shader;

public:
	sample_object(void)
	{
		AttachComponent(std::make_shared<model>());
		AttachComponent(std::make_shared<sdr2222>());
	}
};