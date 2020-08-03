
#pragma once

#include "dotth.h"
#include "ResourceRHI.h"

class IResourceArray;
class VertexBufferRHI;
class IndexBufferRHI;
class DynamicRHI
{
public:
	void* _NativeDevice;
	void* _NativeContext;
	virtual bool Init(void* handle, int width, int height) = 0;
	virtual void PreDraw(void) {}
	virtual void PostDraw(void) {}
	
	template <typename Ty>
	Ty* GetNativeDevice(void)
	{
		return static_cast<Ty*>(_NativeDevice);
	}

	template <typename Ty>
	Ty* GetNativeContext(void)
	{
		return static_cast<Ty*>(_NativeContext);
	}

	virtual VertexBufferRHI* CreateVertexBuffer(unsigned int size, unsigned int usage, IResourceArray* resource_info) = 0;
	virtual IndexBufferRHI* CreateIndexBuffer(unsigned int size, unsigned int usage, IResourceArray* resource_info) = 0;

};