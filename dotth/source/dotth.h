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

#include "external/json/json.hpp"
#include "external/xml/tinyxml2.h"
#include "external/task/task.h"

#include "graphics/dx11/dx11_device.h"

template <size_t Alignment>
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


namespace dotth {
};