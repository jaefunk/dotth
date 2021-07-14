#include "SampleObject.h"

#include "StaticMeshComponent.h"

SampleObject::SampleObject(void)
{
}

void SampleObject::OnInit(void)
{
}

void SampleObject::OnDestroy(void)
{
}

void SampleObject::OnUpdate(void)
{	
	RotateYaw(0.005f);
	RotatePitch(0.005f);
}

void SampleObject::OnDraw(void)
{
}
