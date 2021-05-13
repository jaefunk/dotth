#include "SampleObject.h"

#include "StaticMeshComponent.h"

SampleObject::SampleObject(void)
{
}

void SampleObject::OnInit(void)
{
	//auto jj = std::make_shared< StaticMeshComponent>();
	//_StaticMesh = AddComponent<StaticMeshComponent>();
	//_StaticMesh->LoadMesh()

	//Matrix A, B, R;
	//A.rc[0][0] = 1; A.rc[0][1] = 2; A.rc[0][2] = 3; A.rc[0][3] = 5;
	//A.rc[1][0] = 2; A.rc[1][1] = 4; A.rc[1][2] = 3; A.rc[1][3] = 1;
	//A.rc[2][0] = 4; A.rc[2][1] = 3; A.rc[2][2] = 2; A.rc[2][3] = 3;
	//A.rc[3][0] = 3; A.rc[3][1] = 5; A.rc[3][2] = 4; A.rc[3][3] = 2;

	//B.rc[0][0] = 3; B.rc[0][1] = 1; B.rc[0][2] = 3; B.rc[0][3] = 4;
	//B.rc[1][0] = 2; B.rc[1][1] = 1; B.rc[1][2] = 4; B.rc[1][3] = 5;
	//B.rc[2][0] = 4; B.rc[2][1] = 5; B.rc[2][2] = 2; B.rc[2][3] = 2;
	//B.rc[3][0] = 3; B.rc[3][1] = 1; B.rc[3][2] = 4; B.rc[3][3] = 3;
	

	//Transform tf;
	//tf.Translate({ 1.f, 0.f, 0.f });
	//tf.Scaling(2.f);
	//Transform tf;
	//tf.RotateYaw(PI);
	//auto jj = tf.ToMatrix(true);
	_StaticMesh = AddComponent<StaticMeshComponent>();
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
