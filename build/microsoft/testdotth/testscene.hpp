
#include "base/scene.hpp"
#include "renderer/rectangle.hpp"

class testscene : public dotth::scene {
	virtual void init(json data) override;
	virtual void update(const float delta) override;;
	//virtual void draw(const dotth::matrix4& transform, int flags = 0) override {};
};
