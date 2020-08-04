
#pragma once

#include "Components/DrawableComponent.h"

class PrimitiveComponent : public DrawableComponent
{
public:
	struct VertexType
	{
		XMFLOAT3 position;
		XMFLOAT4 color;
	};

public:
	virtual void OnInit(void) override;
	virtual void OnDraw(void) override;
};

