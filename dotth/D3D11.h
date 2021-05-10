#pragma once

#define DIRECTINPUT_VERSION 0x0800

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "d3d11.lib")

#include <d3d11_1.h>
#include <dinput.h>
#include <d3dcompiler.h>
#include <directxmath.h>
#include <D3D11Shader.h>

using namespace DirectX;

template<size_t Alignment>
class AlignedAllocationPolicy
{
public:
	static void* operator new(size_t size)
	{
		return _aligned_malloc(size, Alignment);
	}

	static void operator delete(void* memory)
	{
		_aligned_free(memory);
	}
};