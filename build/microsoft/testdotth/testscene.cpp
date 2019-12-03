
#include "testscene.hpp"

void testscene::init(const json& data) 
{
	{
		
		auto jj = std::make_shared<dotth::rectangle>();
		jj->init();
		attach(jj);
	}
	{
		//auto jj = std::make_shared<dotth::rectangle>();
		//jj->init();
		//jj->load_sprite("cat");
		//attach(jj);
	}
	

	//jj = std::make_shared<dotth::rectangle>();
	//jj->init();
	//jj->add_position_x(1.0f);
	//attach(jj);
}

void testscene::on_update(const float& delta) 
{
	printf("%f\n", dotth::utility::timer::instance()->delta());
}
