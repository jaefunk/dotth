#pragma once

#include "dotth.h"

#ifdef WIN32
constexpr long long time_scale_millisecond = 10000000;
#else
constexpr long long time_scale_millisecond = 1000000;
#endif

namespace utility {
	namespace string {
		std::string format(const char* format, ...);
	}

	class timer
	{
	public:
		timer(void)
		{
			update();
		}
		void update(void)
		{
			_now = time_since_epoch();
			_delta = static_cast<float>(_now - _prev) / static_cast<float>(time_scale_millisecond);
			_prev = _now;
		}
		const float delta(void)
		{
			return _delta;
		}
		std::time_t time_since_epoch(void)
		{
			return std::chrono::system_clock::now().time_since_epoch().count();
		}
	private:
		std::time_t _prev = 0;
		std::time_t _now = 0;
		float _delta = 0.f;
	};
};