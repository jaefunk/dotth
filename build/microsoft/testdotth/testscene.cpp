
#include "testscene.hpp"

void testscene::init(const json& data) 
{
	{
		//auto parent = std::make_shared<dotth::cube>();
		//parent->init();
		//parent->_trans->scl(0.5f, 0.5f, 0.5f);
		//attach(parent);
	}
	auto parent = std::make_shared<dotth::rectangle>();
	parent->init();
	parent->set_color({ 1.f, 0.f, 0.f, 1.f });
	parent->_trans->scl(0.5f, 0.5f, 0.5f);
	attach(parent);

	auto child = std::make_shared<dotth::rectangle>();
	child->init();
	child->set_color({ 0.f, 1.f, 0.f, 1.f });
	child->_trans->scl(0.5f, 0.5f, 0.5f);
	parent->attach(child);

	auto child2 = std::make_shared<dotth::rectangle>();
	child2->init();
	child2->set_color({ 0.f, 0.f, 1.f, 1.f });
	child2->_trans->scl(0.5f, 0.5f, 0.5f);
	child->attach(child2);
}

void testscene::on_update(const float& delta) 
{
	printf("%f\n", dotth::utility::timer::instance()->delta());
}
