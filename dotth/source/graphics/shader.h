
#pragma once

#include "framework/base.h"

class ID3D11DeviceContext;
class shader : public base
{
public:
	void draw(ID3D11DeviceContext* pContext);
};
