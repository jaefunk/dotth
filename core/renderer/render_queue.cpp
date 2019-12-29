#include "render_queue.hpp"

void dotth::render_queue::push_back(dotth::render::command::inherit * command)
{
	commands.push_back(command);
}

void dotth::render_queue::clear(void) {
	commands.clear();
}

void dotth::render_queue::process(void) const
{
	std::for_each(std::rbegin(commands), std::rend(commands), [](dotth::render::command::inherit* p) {
		p->draw();
	});
}
