#include "StaticMeshComponent.h"
#include "D3D11StaticMesh.h"
#include "Object.h"

void StaticMeshComponent::OnInit(void)
{	
	_StaticMesh = std::make_shared<D3D11StaticMesh>();
	_StaticMesh->Load("Resource/model/robot/RobotKyle.fbx");

	_Shader = std::make_shared<D3D11Shader>();
	_Shader->Load("Resource/Primitive2.hlsl");
}

void StaticMeshComponent::OnUpdate(void)
{
	
}

void StaticMeshComponent::OnDraw(void)
{
	_StaticMesh->Draw();
	_Shader->Draw(GetOwner()->GetTransform().GetWorldMatrix(), static_cast<unsigned int>(_StaticMesh->Indices.size()));
}

void StaticMeshComponent::OnDestroy(void)
{
}


