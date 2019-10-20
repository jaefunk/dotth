
#include "base/scene.hpp"

class testscene : public dotth::scene {
    virtual void init(json data) override {
        
    }
    virtual void update(float delta) override {
        //printf("a %f\n", dotth::utility::timer::instance()->delta());
    };
    virtual void draw(const dotth::matrix4& transform, int flags = 0) override {
    };
};
