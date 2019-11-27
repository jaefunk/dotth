/*
Licensed under the MIT License <http://opensource.org/licenses/MIT>.
Copyright (c) 2019 jaefunk <https://github.com/jaefunk/dotth>.

Permission is hereby  granted, free of charge, to any  person obtaining a copy
of this software and associated  documentation files (the "Software"), to deal
in the Software  without restriction, including without  limitation the rights
to  use, copy,  modify, merge,  publish, distribute,  sublicense, and/or  sell
copies  of  the Software,  and  to  permit persons  to  whom  the Software  is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE  IS PROVIDED "AS  IS", WITHOUT WARRANTY  OF ANY KIND,  EXPRESS OR
IMPLIED,  INCLUDING BUT  NOT  LIMITED TO  THE  WARRANTIES OF  MERCHANTABILITY,
FITNESS FOR  A PARTICULAR PURPOSE AND  NONINFRINGEMENT. IN NO EVENT  SHALL THE
AUTHORS  OR COPYRIGHT  HOLDERS  BE  LIABLE FOR  ANY  CLAIM,  DAMAGES OR  OTHER
LIABILITY, WHETHER IN AN ACTION OF  CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE  OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef __DOTTH_UTILITY_HPP__
#define __DOTTH_UTILITY_HPP__

#include "dotth.hpp"

constexpr long long time_scale_millisecond = 1000;

namespace dotth {
    namespace utility {
		namespace string {
			std::string format(const char* format, ...);
		}
		void sleep(int millisec);
        template<typename ty>
        class singleton {
        public:
            static const std::shared_ptr<ty>& instance() {
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
            timer(void) { update(); }
            void update(void) {
                _now = time_since_epoch();
                _delta = _now - _prev;
                _prev = _now;
            }
            const float delta(void) {
                return static_cast<float>(_delta) / static_cast<float>(time_scale_millisecond);
            }
            std::time_t time_since_epoch(const long long time_scale = time_scale_millisecond) {
                return std::chrono::system_clock::now().time_since_epoch().count() / time_scale;
            }
        private:
            std::time_t _prev = 0;
            std::time_t _now = 0;
            std::time_t _delta = 0;
        };
    };
};

#endif // __DOTTH_UTILITY_HPP__
