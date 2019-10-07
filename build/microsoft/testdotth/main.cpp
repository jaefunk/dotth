

#include "base/scene.hpp"
#include "platform/application.hpp"
#include "testscene.hpp"
#include "platform/filesystem/io.hpp"
int main(int argc, char * argv[]) {
	dotth::io::read_text("asdf.txt");
	dotth::io::read_binary("usagi.png");
	dotth::scene_manager::instance()->assign_scene<testscene>("testscene");
	dotth::scene_manager::instance()->push("testscene", "1234");
	dotth::application::instance()->init(argc, argv);
	return dotth::application::instance()->process();
}
