#include "scene.hpp"
#include "script/node_parser.hpp"

bool dotth::scene::loadview(const std::string& path) {
	auto const& file = node_parser::instance()->read_file(path.c_str());
	auto aa = node_parser::instance()->parse(file);
	return true;
}
