#include "EntryPoint.h"
#include "SampleObject.h"

void EntryPoint::OnInit(void)
{
	std::shared_ptr<SampleObject> so = std::make_shared<SampleObject>();
	AddObject(so);	
}

void EntryPoint::OnDestroy(void)
{
}

void EntryPoint::OnUpdate(void)
{
}

void EntryPoint::OnDraw(void)
{
}