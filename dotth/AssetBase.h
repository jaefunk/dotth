#pragma once

#include "dotth.h"

enum class EXTENSION_TYPE {	
	JPEG,
	FBX,
};

class Resource 
{
public:
	virtual std::shared_ptr<Resource> Clone(void) = 0;
};