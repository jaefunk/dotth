#include "StaticMeshComponent.h"
#include "D3D11StaticMesh.h"
#include "D3D11Texture2D.h"
#include "Object.h"

void StaticMeshComponent::OnInit(void)
{	
	_StaticMesh = std::make_shared<D3D11StaticMesh>();
	_StaticMesh->Load("Resource/model/robot/RobotKyle.fbx");

	_Texture2D = std::make_shared<D3D11Texture2D>();
	_Texture2D->Load("Resource/model/robot/Robot_Color.jpg");

	_Shader = std::make_shared<D3D11Shader>();
	_Shader->Load("Resource/Primitive2.hlsl");
}

void StaticMeshComponent::OnUpdate(void)
{
	
}

void StaticMeshComponent::OnDraw(void)
{
	for (unsigned int i = 0; i < _StaticMesh->GetSectionSize(); ++i)
	{
		_StaticMesh->Draw(i);
		_Texture2D->Draw(i);
		_Shader->Draw(GetOwner()->GetTransform().GetWorldMatrix(), _StaticMesh->GetIndicesSize(i));
	}
}

void StaticMeshComponent::OnDestroy(void)
{
}


