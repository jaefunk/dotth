#include "application.hpp"
#include "renderer/renderer.hpp"

void dotth::application::init(int argc, char ** argv) {
	
	refresh_thread = std::thread([this](int argc, char** argv) {
	}, argc, argv);
	render_thread = std::thread([](int argc, char** argv) {
	}, argc, argv);
	renderer::instance()->init_gl(argc, argv);
}

int dotth::application::process(void) {
    while(true) {
		printf("as");
    }
	return 0;
}
