#include "EntryPoint.h"
#include "SampleObject.h"

void EntryPoint::OnInit(void)
{
	SetCameraPosition(Float3(0.f, 90.f, -250.f));
	SetCameraLookAt(Float3(0.f, 0.f, 0.f));
	SetCameraUp(Float3(0.f, 1.f, 0.f));
	SetCameraFrustumFieldOfView(3.141592f * 0.25f);
	SetCameraFrustumNearFieldDistance(0.1f);
	SetCameraFrustumFarFieldDistance(1000.f);
	
	{
		std::shared_ptr<SampleObject> A = std::make_shared<SampleObject>();
		//std::shared_ptr<SampleObject> B = std::make_shared<SampleObject>();
		//std::shared_ptr<SampleObject> C = std::make_shared<SampleObject>();
		//std::shared_ptr<SampleObject> D = std::make_shared<SampleObject>();
		//std::shared_ptr<SampleObject> E = std::make_shared<SampleObject>();

		A->Rename("A");
		//B->Rename("B");
		//C->Rename("C");
		//D->Rename("D");
		//E->Rename("E");		

		//A->AddChild(B);
		//B->AddChild(C);
		//C->AddChild(D);
		//D->AddChild(E);

		//A->Scaling(0.5f);
		//B->Scaling(0.5f);
		//C->Scaling(0.5f);		
		//D->Scaling(0.5f);
		//E->Scaling(0.5f);

		//B->TranslateY(1.f);
		//C->TranslateY(1.f);
		//D->TranslateY(1.f);
		//E->TranslateY(1.f);

		SpawnObject(A);
	}
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