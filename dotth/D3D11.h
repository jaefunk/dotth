#pragma once

#define DIRECTINPUT_VERSION 0x0800

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")

#include <d3d11_1.h>
#include <dxgi.h>
#include <d3dcompiler.h>
#include <directxmath.h>
#include <d3d11shader.h>

using namespace DirectX;

enum DEFERRED_RENDER_TARGET_TYPE {
	POSITION,
	DIFFUSE,
	NORMAL,
	DEFERRED_RENDER_TARGET_TYPE_MAX,
};

//template<size_t Alignment>
//class AlignedAllocationPolicy
//{
//public:
//	static void* operator new(size_t size)
//	{
//		return _aligned_malloc(size, Alignment);
//	}
//
//	static void operator delete(void* memory)
//	{
//		_aligned_free(memory);
//	}
//};