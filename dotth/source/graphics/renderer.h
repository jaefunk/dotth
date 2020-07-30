
#pragma once

#include "Graphics/RHI/D11/D11RHI.h"
#include "utility/SingleInstance.h"

class renderer : public SingleInstance<renderer>
{
private:
	D11RHI _dx11;
	
public:	
	static ID3D11Device* device(void) {
		return renderer::Instance()->_dx11.device();
	}
	static ID3D11DeviceContext* context(void) {
		return renderer::Instance()->_dx11.context();
	}
	static D11RHI* RHI(void) {
		return &renderer::Instance()->_dx11;
	}

public:
	bool Init(void* handle, int width, int height);
	void clear_buffer(void)
	{
		_dx11.PreDraw();
	}
	void swap_buffer(void)
	{
		_dx11.PostDraw();
	}
};

/*

#pragma once
#include "Graphics/RHI/DynamicRHI.h"
#include "utility/SingleInstance.h"

class renderer : public SingleInstance<renderer>
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