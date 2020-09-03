#pragma once

#include <stdarg.h>
#include <string>
#include <vector>

namespace Utility {
	namespace Str {
		std::string Format(const char* format, ...);
		std::vector<std::string> Split(std::string src, std::string token);
	}

	//class timer
	//{
	//public:
	//	timer(void)
	//	{
	//		update();
	//	}
	//	void update(void)
	//	{
	//		_now = time_since_epoch();
	//		_delta = static_cast<float>(_now - _prev) / static_cast<float>(time_scale_millisecond);
	//		_prev = _now;
	//	}
	//	const float delta(void)
	//	{
	//		return _delta;
	//	}
	//	std::time_t time_since_epoch(void)
	//	{
	//		return std::chrono::system_clock::now().time_since_epoch().count();
	//	}
	//private:
	//	std::time_t _prev = 0;
	//	std::time_t _now = 0;
	//	float _delta = 0.f;
	//};
};