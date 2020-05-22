#include "scene.h"

bool dotth::scene::loadview(const std::string& path) 
{
	return true;
}


void dotth::scene_manager::update(void) {
    apply_new_scene();
    if (_current == nullptr)
        return;
    _current->update();
}
