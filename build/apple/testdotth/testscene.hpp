
#include "base/scene.hpp"
#include "base/drawable.hpp"
class testscene : public dotth::scene {
    virtual void init(json data) override {
//        auto kk = std::make_shared<dotth::rectangle>();
//        kk->init1();
//        attach(kk);
        auto jj = std::make_shared<dotth::rectangle>();
        jj->init2();
        attach(jj);
        
        
    }
    virtual void update(float delta) override {
        //printf("a %f\n", dotth::utility::timer::instance()->delta());
    };
    virtual void draw(const dotth::matrix4& transform, int flags = 0) override {
    };
};
