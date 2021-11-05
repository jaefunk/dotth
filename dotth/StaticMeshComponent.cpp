#include "StaticMeshComponent.h"
#include "D3D11StaticMesh.h"
#include "D3D11Texture2D.h"
#include "Camera.h"

void StaticMeshComponent::OnInit(void)
{	
	
}

void StaticMeshComponent::Load1(void)
{
	_StaticMesh = std::make_shared<D3D11StaticMesh>();
	_StaticMesh->Load("Sphere");

	_Texture2D = std::make_shared<D3D11Texture2D>();
	_Texture2D->Load("uv_checker");

	//_Shader = std::make_shared<D3D11Shader>();
	//_Shader->Load("Resource/Primitive2.hlsl");

	_DeferredVertexShader = std::make_shared<SimpleVertexShader>(D3D11RHI::Device(), D3D11RHI::Context());
	_DeferredVertexShader->LoadShaderFile(L"../Output/Client/x64/Debug/deferred_vs.cso");

	_DeferredPixelShader = std::make_shared<SimplePixelShader>(D3D11RHI::Device(), D3D11RHI::Context());
	_DeferredPixelShader->LoadShaderFile(L"../Output/Client/x64/Debug/deferred_ps.cso");
}

void StaticMeshComponent::Load2(void)
{
	_StaticMesh = std::make_shared<D3D11StaticMesh>();
	_StaticMesh->Load("Plane");

	_Texture2D = std::make_shared<D3D11Texture2D>();
	_Texture2D->Load("uv_checker");

	//_Shader = std::make_shared<D3D11Shader>();
	//_Shader->Load("Resource/Primitive2.hlsl");

	_DeferredVertexShader = std::make_shared<SimpleVertexShader>(D3D11RHI::Device(), D3D11RHI::Context());
	_DeferredVertexShader->LoadShaderFile(L"../Output/Client/x64/Debug/deferred_vs.cso");

	_DeferredPixelShader = std::make_shared<SimplePixelShader>(D3D11RHI::Device(), D3D11RHI::Context());
	_DeferredPixelShader->LoadShaderFile(L"../Output/Client/x64/Debug/deferred_ps.cso");
}

void StaticMeshComponent::Load3(void)
{
	_StaticMesh = std::make_shared<D3D11StaticMesh>();
	_StaticMesh->Load("Plane");

	_Texture2D = std::make_shared<D3D11Texture2D>();
	_Texture2D->Load("uv_checker");

	//_Shader = std::make_shared<D3D11Shader>();
	//_Shader->Load("Resource/Primitive2.hlsl");

	_DeferredVertexShader = std::make_shared<SimpleVertexShader>(D3D11RHI::Device(), D3D11RHI::Context());
	_DeferredVertexShader->LoadShaderFile(L"../Output/Client/x64/Debug/deferred_vs.cso");

	_DeferredPixelShader = std::make_shared<SimplePixelShader>(D3D11RHI::Device(), D3D11RHI::Context());
	_DeferredPixelShader->LoadShaderFile(L"../Output/Client/x64/Debug/deferred_ps.cso");
}

void StaticMeshComponent::OnUpdate(void)
{
}

void StaticMeshComponent::OnDraw(void)
{
	XMFLOAT4X4 world, view, proj;
	XMStoreFloat4x4(&world, GetOwner()->GetTransform().GetWorldMatrix());
	XMStoreFloat4x4(&view, XMMatrixTranspose(GetOwner()->GetActiveCamera()->GetView()));
	XMStoreFloat4x4(&proj, XMMatrixTranspose(GetOwner()->GetActiveCamera()->GetPerspective()));
	
	for (unsigned int i = 0; i < _StaticMesh->GetSectionSize(); ++i)
	{
		_StaticMesh->Draw(i);
		_Texture2D->Draw(i);
		
		_DeferredVertexShader->SetMatrix4x4("world", world);
		_DeferredVertexShader->SetMatrix4x4("view", view);
		_DeferredVertexShader->SetMatrix4x4("projection", proj);
		_DeferredVertexShader->CopyAllBufferData();
		_DeferredVertexShader->SetShader();
		
		_DeferredPixelShader->SetSamplerState("Sampler", D3D11RHI::Sampler());
		_DeferredPixelShader->SetShaderResourceView("Texture", _Texture2D->GetShaderResourceView());
		_DeferredPixelShader->CopyAllBufferData();
		_DeferredPixelShader->SetShader();
		
		D3D11RHI::Context()->DrawIndexed(_StaticMesh->GetIndicesSize(i), 0, 0);
	}
}

void StaticMeshComponent::OnDestroy(void)
{
}


