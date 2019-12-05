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
