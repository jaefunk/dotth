#pragma once

#include <cstring>
#include <string>
#include <ctime>
#include <atomic>
#include <memory>
#include <chrono>
#include <mutex>
#include <unordered_map>
#include <stack>
#include <vector>
#include <list>
#include <queue>
#include <set>
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

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dx11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include <directxcolors.h>

// include external...
#include "json/json.hpp"
#include "xml/tinyxml2.h"
//#define _WIN32_WINNT 0x0501
//#define WIN32_LEAN_AND_MEAN
//#include "asio/asio.hpp"

#include "Utility/Utility.h"

namespace dotth 
{
};

// convention...
//
// class name:				PascalCase
// all function name:		PascalCase
// class member variable:	_PascalCase
// function parameter:		camelCase
// function local variable: snake_case
