#include "sample_object.h"


#include "Components/CubeComponent.h"
#include "Components/SpriteComponent.h"
#include "Components/ModelComponent.h"

sample_object::sample_object(void)
{
	auto sc = std::make_shared<SpriteComponent>("cat0");
	AttachComponent(sc);

	auto mc = std::make_shared<ModelComponent>("robot1");
	AttachComponent(mc);


	//auto model = new Asset_Model;
	//model->Load("Resource/model/Robot Kyle/Model/RobotKyle.fbx");

}
