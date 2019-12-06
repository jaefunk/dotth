#include "render_queue.hpp"
#include "base/drawable.hpp"

void dotth::render_queue::push_back(dotth::drawable* drawable)
{
	drawables.push_back(drawable);
}

void dotth::render_queue::push_back(dotth::render::command::inherit * command)
{
	commands.push_back(command);
}

void dotth::render_queue::clear(void) {
	drawables.clear();
}

void dotth::render_queue::process(void) const
{
	std::for_each(std::begin(drawables), std::end(drawables), [](dotth::drawable* p) {
		p->draw(0);
	});
	std::for_each(std::begin(commands), std::end(commands), [](dotth::render::command::inherit* p) {
		p->draw();
	});
}
