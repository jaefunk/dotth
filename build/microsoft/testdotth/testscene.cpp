
#include "testscene.hpp"

void testscene::init(const json& data) 
{
	auto parent = std::make_shared<dotth::rectangle>();
	parent->init();
	parent->set_color({ 1.f, 0.f, 0.f, 1.0f });
	//parent->trans.rot_z(45.f);
	//parent->trans.pos_z(10.f);
	attach(parent);

	auto child = std::make_shared<dotth::rectangle>();
	child->init();
	child->set_color({ 0.f, 1.f, 0.f, 1.f });
	child->trans.pos_x(0.5f);
	child->trans.pos_y(0.5f);
	child->trans.pos_z(-0.1f);

	
	parent->attach(child);
}

void testscene::on_update(const float& delta) 
{
	printf("%f\n", dotth::utility::timer::instance()->delta());
}
