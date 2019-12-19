
#include "resource.hpp"
#include "texture.hpp"
#include "shader.hpp"

const bool dotth::resource_manager::load(dotth::type::resource res_type, const char* path, const char* name) {
    if (name == nullptr)
        name = path;
    switch (res_type) {
        case dotth::type::resource::text:
            break;
        case dotth::type::resource::image: {
            std::shared_ptr<texture> p = std::make_shared<texture>();
            p->load(path);
			p->_res_type = res_type;
            resource_container.insert({name, p});
            break;
        }
        case dotth::type::resource::mesh:
            break;
		case dotth::type::resource::shader: {
			std::shared_ptr<shader> p = std::make_shared<shader>();
			p->load(path);
			p->_res_type = res_type;
			resource_container.insert({ name, p });
			break;
		}
        default:
            break;
    }
    return true;
}
