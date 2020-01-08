#ifndef __DOTTH_UTILITY_HPP__
#define __DOTTH_UTILITY_HPP__

#include "dotth.hpp"

#ifdef WIN32
constexpr long long time_scale_millisecond = 10000000;
#else
constexpr long long time_scale_millisecond = 1000000;
#endif

namespace dotth {
    namespace utility {
		namespace string {
			std::string format(const char* format, ...);
		}
		
        template<typename ty>
        class singleton {
        public:
            static const std::shared_ptr<ty>& instance() 
			{
                std::call_once(_flag, []() {
                    _instance = std::make_shared<ty>();
                });
                return _instance;
            }
        private:
            static std::once_flag _flag;
            static std::shared_ptr<ty> _instance;
        };
        template<typename ty> std::once_flag utility::singleton<ty>::_flag;
        template<typename ty> std::shared_ptr<ty> utility::singleton<ty>::_instance;
        
        class timer : public singleton<timer> {
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
};

#endif // __DOTTH_UTILITY_HPP__
