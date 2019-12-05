#include "drawable.hpp"
#include "renderer/renderer.hpp"

void dotth::drawable::set_shader(const char * key)
{
	_shader = dotth::shader_manager::instance()->find(key);
	if (_shader == nullptr)
		printf("%s is not valid shader", key);
}

void dotth::drawable::on_push_render_queue(void)
{
	dotth::renderer::instance()->push_back(this);
}
