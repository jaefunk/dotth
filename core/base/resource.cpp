#include "resource.hpp"
#include "renderer/texture.hpp"

const bool dotth::resource_manager::load(dotth::type::resource res_type, const char* path, const char* name) {
    if (name == nullptr)
        name = path;
    switch (res_type) {
        case dotth::type::resource::text:
            
            break;
        case dotth::type::resource::image: {
            std::shared_ptr<texture> p = std::make_shared<texture>();
            p->load(path);
            resource_container.insert({name, p});
            break;
        }
        case dotth::type::resource::mesh:
            break;
        default:
            break;
    }
    return true;
}
