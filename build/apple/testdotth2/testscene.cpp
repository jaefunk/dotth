
#include "testscene.hpp"

void testscene::init(const json& data) 
{
	auto parent = std::make_shared<dotth::rectangle>();
	parent->init();
	parent->set_color({ 1.f, 0.f, 0.f, 1.f });
	parent->trans.set_ortho(true);
	parent->trans.size(100.f, 100.f);
	parent->trans.pos(-512.f + 50.f, -50.f);
	
	//parent->trans.scl((1.f/512.f) * 100.f);
	attach(parent);

	auto child = std::make_shared<dotth::rectangle>();
	child->init();
	child->set_color({ 0.f, 1.f, 0.f, 1.f });
	child->trans.pos_x(50.f);
	child->trans.size(50.f, 50.f);
	child->trans.set_ortho(true);
	parent->attach(child);

	//auto child2 = std::make_shared<dotth::rectangle>();
	//child2->init();
	//child2->set_color({ 0.f, 0.f, 1.f, 1.f });
	//child2->trans.pos_x(50.f);
	////child2->trans.size(25.f, 25.f);
	//child2->trans.set_ortho(true);
	//child ->attach(child2);
}

void testscene::on_update(const float& delta) 
{
	printf("%f\n", dotth::utility::timer::instance()->delta());
}
