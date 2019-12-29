
#include "base/scene.hpp"
#include "renderer/primitive.hpp"

class testscene : public dotth::scene {
    virtual void init(const json& data) override;
    virtual void on_update(const float& delta) override;
    virtual void on_keyboard_input(const std::list<dotth::keyboard>& _inputs) override;
    virtual void on_mouse_input(const std::list<dotth::mouse>& _inputs) override;
};
