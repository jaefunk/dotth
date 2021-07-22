#pragma once

#include "Asset2d.h"

class Texture2D : public TextureBase
{
	virtual void Draw(const unsigned int& index) = 0;
};