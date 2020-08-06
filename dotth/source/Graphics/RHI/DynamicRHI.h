
#pragma once

#include "dotth.h"
#include "ResourceRHI.h"

class IDataSize;
class VertexBufferRHI;
class IndexBufferRHI;
class BufferRHI;
class DynamicRHI
{
public:
	virtual bool Init(void* handle, int width, int height) = 0;
	virtual void PreDraw(void) {}
	virtual void PostDraw(void) {}

	virtual void* GetNativeDevice(void) = 0;
	virtual void* GetNativeContext(void) = 0;
	virtual VertexBufferRHI* CreateVertexBuffer(unsigned int size, unsigned int usage, IDataSize* resource_info) = 0;
	virtual IndexBufferRHI* CreateIndexBuffer(unsigned int size, unsigned int usage, IDataSize* resource_info) = 0;

	virtual VertexShaderRHI* CreateVertexShader(std::string file_path, void* vertex_desc, unsigned int num_desc) = 0;
	virtual PixelShaderRHI* CreatePixelShader(std::string file_path) = 0;
	
	virtual void BindVertexBuffer(VertexBufferRHI* buffer, unsigned int stride, unsigned int offset) {}
	virtual void BindIndexBuffer(IndexBufferRHI* buffer, unsigned int format, unsigned int offset) {}
	virtual void BindVertexShader(VertexShaderRHI* shader) {}
	virtual void BindPixelShader(PixelShaderRHI* shader) {}
	virtual void VSSetConstantBuffers(unsigned int start, unsigned int num, void* buffer) {}
	virtual void PSSetConstantBuffers(unsigned int start, unsigned int num, void* buffer) {}
	virtual void PSSetResources(unsigned int start, unsigned int num, void* buffer) {}
	virtual void PSSetSamplers(unsigned int start, unsigned int num, void* buffer) {}
	virtual void BindTexture(void) {}
};