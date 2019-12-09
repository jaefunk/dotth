#include "drawable.hpp"
#include "renderer/renderer.hpp"

void dotth::drawable::on_push_render_queue(void)
{
	dotth::renderer::instance()->push_back(_command.get());
}
