#include "SampleObject.h"

#include "StaticMeshComponent.h"

SampleObject::SampleObject(void)
{
}

void SampleObject::OnInit(void)
{
	_StaticMesh = AddComponent<StaticMeshComponent>();
}

void SampleObject::OnDestroy(void)
{
}

void SampleObject::OnUpdate(void)
{
	RotateYaw(0.1f);
}

void SampleObject::OnDraw(void)
{
}
