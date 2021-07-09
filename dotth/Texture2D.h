#pragma once

#include "Asset2d.h"

class Texture2D : public texture
{
public:
	virtual void Load(const std::string& path) = 0;
	virtual void Draw(const unsigned int& index) = 0;
};