
#pragma once

#include "dotth.h"
#include "ResourceRHI.h"

class IResourceArrayInfo;
class VertexBufferRHI;
class IndexBufferRHI;
class DynamicRHI
{
public:
	virtual bool Init(void* handle, int width, int height) = 0;
	virtual void PreDraw(void) {}
	virtual void PostDraw(void) {}
	
	virtual void* GetNativeDevice(void) = 0;

	virtual VertexBufferRHI* CreateVertexBuffer(uint32_t size, uint32_t usage, IResourceArrayInfo& resource_info) = 0;
	virtual IndexBufferRHI* CreateIndexBuffer(void) = 0;

};