
#include "DrawableComponent.h"

DrawableComponent::~DrawableComponent(void)
{
	if (_VertexBuffer)
		_VertexBuffer->Release();
	if (_IndexBuffer)
		_IndexBuffer->Release();
}
