
#include "base/scene.hpp"


#include "renderer/primitive.hpp"
class testscene : public dotth::scene {
    virtual void init(json data) override {
        auto kk = std::make_shared<dotth::rectangle>();
        kk->init();
        kk->add_position_x(0.25f);
        kk->load_sprite("cat");
        attach(kk);
        auto jj = std::make_shared<dotth::rectangle>();
        jj->init();
        jj->add_position_x(-0.25f);
        jj->load_sprite("usagi");
        attach(jj);
        
        
        
//        auto kk = std::make_shared<dotth::cube>();
//        kk->init();
//        attach(kk);
    }
    virtual void update(float delta) override {
        //printf("a %f\n", dotth::utility::timer::instance()->delta());
    };
    virtual void draw(int flags = 0) override {
    };
};
