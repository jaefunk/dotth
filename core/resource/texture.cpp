#include "texture.hpp"

bool dotth::texture::load(const char * path) {
	_res_name = path;
	stbi_set_flip_vertically_on_load(true);
	_data = stbi_load(dotth::path(path).c_str(), &_width, &_height, &_comp, 0);
	_texture_id = initGL(_width, _height, GL_RGB, GL_RGBA, GL_UNSIGNED_BYTE, _data);
	return true;
}
