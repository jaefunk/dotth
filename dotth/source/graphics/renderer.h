
#pragma once

#include "utility/SingleInstance.h"
#include "Graphics/RHI/D11/D11RHI.h"

class Renderer : public SingleInstance<Renderer>
{
private:
	DynamicRHI* _RHI;
	
public:	
	static ID3D11Device* device(void) {
		return static_cast<ID3D11Device*>(Renderer::Instance()->_RHI->GetNativeDevice());
	}
	static ID3D11DeviceContext* context(void) {
		return static_cast<ID3D11DeviceContext*>(Renderer::Instance()->_RHI->GetNativeContext());
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
