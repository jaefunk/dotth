#include "SampleObject.h"

#include "StaticMeshComponent.h"

SampleObject::SampleObject(void)
{
}

void SampleObject::OnInit(void)
{
	//auto jj = std::make_shared< StaticMeshComponent>();
	_StaticMesh = AddComponent<StaticMeshComponent>();
	//_StaticMesh->LoadMesh()
}

void SampleObject::OnDestroy(void)
{
}

void SampleObject::OnUpdate(void)
{
}

void SampleObject::OnDraw(void)
{
}
