#pragma once

#include "Windows.h"

// stl
#include <cstring>
#include <string>
#include <ctime>
#include <atomic>
#include <memory>
#include <chrono>
#include <mutex>
#include <unordered_map>
#include <map>
#include <stack>
#include <vector>
#include <list>
#include <queue>
#include <set>
#include <array>
#include <algorithm>
#include <future>
#include <thread>
#include <fstream>
#include <sstream>
#include <cmath>
#include <stdarg.h>
#include <type_traits>
#include <functional>
#include <iostream>
#include <filesystem>
#include <limits>

// imgui
#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_win32.h"
#include "imgui/backends/imgui_impl_dx11.h"

// directx
#define DIRECTINPUT_VERSION 0x0800
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")
#include <d3d11_1.h>
#include <dxgi.h>
#include <directxmath.h>
#include <d3dcompiler.h>
#include <directxmath.h>
#include <d3d11shader.h>
using namespace DirectX;

// dotth
#include "Math/Vector2.h"
#include "Math/Vector3.h"
#include "Math/Vector4.h"
#include "Math/Matrix.h"
#include "Math/Transform.h"

#include "Base.h"
#include "SystemDefine.h"
#include "SingleInstance.h"

namespace dotth 
{
};

/*
to do list {
	deferred rendering		- done
	resource manager		- done
	directional light		- done
	imgui					- done
	arrange					- done
	user input				- work
	skeletal mesh			- work
	particle				- yet
}
*/ 
