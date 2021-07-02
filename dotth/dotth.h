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

#include "External/imgui/imgui.h"
#include "External/imgui/backends/imgui_impl_dx11.h"
#include "External/imgui/backends/imgui_impl_win32.h"

#include "Math/Math.h"

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
