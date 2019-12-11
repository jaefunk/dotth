
#include "testscene.hpp"

void testscene::init(const json& data) 
{
	auto parent = std::make_shared<dotth::rectangle>();
	parent->init();
	parent->set_color({ 1.f, 0.f, 0.f, 1.f });
	
	//parent->trans.scl((1.f/512.f) * 100.f);
	attach(parent);

	auto child = std::make_shared<dotth::rectangle>();
	child->init();
	child->set_color({ 0.f, 1.f, 0.f, 1.f });
	child->trans3d.pos_x(50.f);
	parent->attach(child);

	
	auto child2 = std::make_shared<dotth::rectangle>();
	child2->init();
	child2->set_color({ 0.f, 0.f, 1.f, 1.f });
	child ->attach(child2);

	parent->trans3d.scl(0.5f);
}

void testscene::on_update(const float& delta) 
{
	printf("%f\n", dotth::utility::timer::instance()->delta());
}
