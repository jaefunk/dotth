
#pragma once

#include "utility/SingleInstance.h"
#include "Graphics/RHI/D11/D11RHI.h"

class Renderer : public SingleInstance<Renderer>
{
private:
	D11RHI* _RHI;
	
public:	
	static D11RHI* RHI(void);

public:
	bool Init(void* handle, int width, int height);
	void clear_buffer(void);
	void swap_buffer(void);
};
