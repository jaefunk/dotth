#pragma once

#include "dotth.h"

enum class EXTENSION_TYPE {	
	JPEG,
	FBX,
};

struct AssetBase
{
public:
	virtual bool Load(const std::string& path) = 0;
};