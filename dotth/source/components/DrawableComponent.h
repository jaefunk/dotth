#pragma once

#include "Framework/Component.h"
#include "Graphics/Renderer.h"

//template <class VertexType, class ShaderType>
class DrawableComponent : public Component
{
protected:
	ID3D11Buffer* _VertexBuffer = nullptr;
	ID3D11Buffer* _IndexBuffer = nullptr;

public:
	virtual ~DrawableComponent(void);
};

