#include "sample_object.h"

#include "Asset/Asset_Text.h"
#include "Asset/Asset_Binary.h"

#include "Components/ModelComponent.h"

sample_object::sample_object(void)
{
	auto sc = std::make_shared<SpriteComponent>();
	AttachComponent(sc);

	AttachComponent(std::make_shared<ModelComponent>());

	auto kk = new Asset_Text;

	kk->Load("Client.cpp");

	auto jj = new Asset_Binary;

	jj->Load("Client.ico");

}
