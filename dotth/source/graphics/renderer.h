
#pragma once

#include "Graphics/RHI/D11/D11RHI.h"
#include "utility/SingleInstance.h"

class Renderer : public SingleInstance<Renderer>
{
private:
	DynamicRHI* _RHI;
	
public:	
	static ID3D11Device* device(void) {
		return Renderer::Instance()->_RHI->GetNativeDevice<ID3D11Device>();
	}
	static ID3D11DeviceContext* context(void) {
		return Renderer::Instance()->_RHI->GetNativeContext<ID3D11DeviceContext>();
	}
	static DynamicRHI* RHI(void) {
		return Renderer::Instance()->_RHI;
	}

public:
	bool Init(void* handle, int width, int height);
	void clear_buffer(void)
	{
		_RHI->PreDraw();
	}
	void swap_buffer(void)
	{
		_RHI->PostDraw();
	}
};

/*

#pragma once
#include "Graphics/RHI/DynamicRHI.h"
#include "utility/SingleInstance.h"

class Renderer : public SingleInstance<Renderer>
{
private:
	std::unique_ptr<DynamicRHI> _RHI;
public:
	void* Device(void) {
		return _RHI->GetNativeDevice();
	}
	void* context(void) {
		return _RHI->GetNativeDevice();
	}

public:
	bool Init(void* handle, int width, int height);
	void clear_buffer(void)
	{
		_RHI->PreDraw();
	}
	void swap_buffer(void)
	{
		_RHI->PostDraw();
	}
};
*/