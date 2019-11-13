
#include "testscene.hpp"

void testscene::init(json data) 
{
	auto jj = std::make_shared<dotth::rectangle>();
	jj->init1();
	attach(jj);
	jj = std::make_shared<dotth::rectangle>();
	jj->init2();
	attach(jj);
}

void testscene::update(float delta) 
{
	printf("%f\n", dotth::utility::timer::instance()->delta());
}
