
#include "base/scene.hpp"
#include "renderer/primitive.hpp"

class testscene : public dotth::scene {
    virtual void init(const json& data) override;
    virtual void on_update(const float& delta) override;
};
