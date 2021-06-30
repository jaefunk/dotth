#include "StaticMeshComponent.h"
#include "D3D11StaticMesh.h"
#include "Object.h"

void StaticMeshComponent::OnInit(void)
{	
	_StaticMesh = std::make_shared<D3D11StaticMesh>();
	_StaticMesh->Load("Resource/model/robot/RobotKyle.fbx");
	//_StaticMesh->Load("Resource/Sphere.FBX");
}

void StaticMeshComponent::OnUpdate(void)
{
	
}

void StaticMeshComponent::OnDraw(void)
{
	_StaticMesh->Matrix = GetOwner()->GetTransform().GetWorldMatrix();
	//_StaticMesh->Matrix.SetIdentity();
	_StaticMesh->Draw();
}

void StaticMeshComponent::OnDestroy(void)
{
}


