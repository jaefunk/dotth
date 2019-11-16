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

#ifndef __DOTTH_RESOURCE_HPP__
#define __DOTTH_RESOURCE_HPP__

#include "base.hpp"
#include "platform/filesystem/path.hpp"

namespace dotth {
    namespace type {
        enum resource {
            none,
            text,
            image,
            mesh,
        };
    };

	class resource : public base {
	public:
        const type::resource res_type(void) { return _res_type; }
        virtual void clear(void) = 0;
        virtual void load(const char* path) = 0;
	protected:
        type::resource _res_type = type::resource::none;
	};

	class resource_manager : public dotth::utility::singleton<resource_manager>
	{
    private:
        std::unordered_map<std::string, std::shared_ptr<resource>> resource_container;
    public:
        const bool load(dotth::type::resource res_type, const char* path, const char* name = nullptr);
        template <typename ty>
        std::shared_ptr<ty> find(const char* name) {
            auto iter = resource_container.find(name);
            if (iter == resource_container.end())
                return nullptr;
            return std::dynamic_pointer_cast<ty>(iter->second);
        }
	};
};

#endif // __DOTTH_RESOURCE_HPP__
