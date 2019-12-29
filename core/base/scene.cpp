#include "scene.hpp"
#include "script/node_parser.hpp"

bool dotth::scene::loadview(const std::string& path) {
	auto const& file = node_parser::instance()->read_file(path.c_str());
	auto aa = node_parser::instance()->parse(file);
	return true;
}


void dotth::scene_manager::update(void) {
    apply_new_scene();
    if (_current == nullptr)
        return;
    _current->on_keyboard_input(dotth::input::instance()->get_keyboard_input());
    _current->on_mouse_input(dotth::input::instance()->get_mouse_input());
    _current->update();
}
