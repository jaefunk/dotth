#include "EntryPoint.h"
#include "SampleObject.h"

void EntryPoint::OnInit(void)
{
	Root()->Attach(std::make_shared<SampleObject>());
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