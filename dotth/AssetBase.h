#pragma once

#include "dotth.h"

enum ASSET_TYPE {
	
	JPEG,
	FBX,
};

struct AssetBase
{
public:
	virtual bool Load(const ASSET_TYPE& type, const std::string& path) = 0;
};