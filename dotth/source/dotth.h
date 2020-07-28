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
