
#include "testscene.hpp"

void testscene::init(const json& data) 
{
	auto jj = std::make_shared<dotth::rectangle>();
	jj->init();
	jj->set_color({ 1.f, 1.f, 0.f, 1.f });
	attach(jj);

	auto kk = std::make_shared<dotth::rectangle>();
	kk->init();
	kk->set_color({ 1.f, 0.f, 1.f, 1.f });
	kk->trans.pos_x(2.f);
	//kk->trans.scale_x(10.f);
	//kk->trans.scale_y(10.f);
	//kk->trans.rotate_x(90.f);
	kk->trans.sync();
	attach(kk); 
}

void testscene::on_update(const float& delta) 
{
	printf("%f\n", dotth::utility::timer::instance()->delta());
}
