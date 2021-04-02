#include "SampleObject.h"
#include "../dotth/PrimitiveComponent.h"

SampleObject::SampleObject(void)
{
}

void SampleObject::OnInit(void)
{
	AddComponent(std::make_shared<PrimitiveComponent>());
}

void SampleObject::OnDestroy(void)
{
}

void SampleObject::OnUpdate(void)
{
	printf("asdf");
}

void SampleObject::OnDraw(void)
{
}
