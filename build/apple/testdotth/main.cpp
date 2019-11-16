
#include "platform/application.hpp"
#include "testscene.hpp"

#include <thread>

int main(int argc, char * argv[]) {

    dotth::scene_manager::instance()->assign_scene<testscene>("testscene");
    dotth::scene_manager::instance()->push("testscene", "1234");
    
    dotth::application::instance()->init(argc, argv);
    return dotth::application::instance()->process();
}
