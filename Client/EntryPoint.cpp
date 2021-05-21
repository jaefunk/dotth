#include "EntryPoint.h"
#include "SampleObject.h"

void EntryPoint::OnInit(void)
{
	SetCameraPosition(Float3(0.f, 0.f, -9.f));
	SetCameraLookAt(Float3(0.f, 0.f, 0.f));
	SetCameraUp(Float3(0.f, 1.f, 0.f));
	SetCameraFrustumFieldOfView(PI * 0.25f);
	SetCameraFrustumNearFieldDistance(0.1f);
	SetCameraFrustumFarFieldDistance(1000.f);
	
	{
		std::shared_ptr<SampleObject> A = std::make_shared<SampleObject>();
		std::shared_ptr<SampleObject> B = std::make_shared<SampleObject>();
		std::shared_ptr<SampleObject> B1 = std::make_shared<SampleObject>();
		std::shared_ptr<SampleObject> C = std::make_shared<SampleObject>();
		std::shared_ptr<SampleObject> D = std::make_shared<SampleObject>();
		std::shared_ptr<SampleObject> E = std::make_shared<SampleObject>();

		A->Rename("A");
		B->Rename("B");
		B1->Rename("B1");
		C->Rename("C");
		D->Rename("D");
		E->Rename("E");


		SpawnObject(A);

		A->AddChild(B);
		A->AddChild(B1);
		B->AddChild(C);
		C->AddChild(D);
		D->AddChild(E);

		B->Scaling(0.5f);
		B1->Scaling(1.f);
		C->Scaling(1.f);		
		D->Scaling(1.f);
		E->Scaling(1.f);

		B->TranslateX(1.f);
		B1->TranslateX(-1.f);
		C->TranslateX(1.f);
		D->TranslateX(1.f);
		E->TranslateX(1.f);

		B->RotateRoll(PI * 0.25f);
		B1->RotateRoll(PI * 0.25f);
		C->RotateRoll(PI * 0.25f);
		D->RotateRoll(PI * 0.25f);
		E->RotateRoll(PI * 0.25f);
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