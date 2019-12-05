
#include "base/scene.hpp"
#include "renderer/primitive.hpp"

class testscene : public dotth::scene {
    virtual void init(const json& data) override {
        auto kk = std::make_shared<dotth::rectangle>();
        kk->init();
        kk->set_color({1.f, 0.f, 0.f, 1.f});
        attach(kk);
    }
    virtual void on_update(const float& delta) override {
        //printf("a %f\n", dotth::utility::timer::instance()->delta());
    };
};
