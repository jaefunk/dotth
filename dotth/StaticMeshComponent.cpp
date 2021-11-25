#include "StaticMeshComponent.h"
#include "Camera.h"

void StaticMeshComponent::OnInit(void)
{	
	
}

bool StaticMeshComponent::SetStaticMesh(std::shared_ptr<StaticMesh> NewMesh)
{
	if (NewMesh == staticMesh)
	{
		return false;
	}

	staticMesh = NewMesh;
	return true;
}

void StaticMeshComponent::Load1(void)
{
	staticMesh = std::make_shared<StaticMesh>();
	staticMesh->Load("Sphere");

	texture2D = std::make_shared<Texture2D>();
	texture2D->Load("uv_checker");

	deferredVertexShader = std::make_shared<VertexShader>(D3D11RHI::Device(), D3D11RHI::Context());
	deferredVertexShader->LoadShaderFile(L"../Output/Client/x64/Debug/deferred_vs.cso");

	deferredPixelShader = std::make_shared<PixelShader>(D3D11RHI::Device(), D3D11RHI::Context());
	deferredPixelShader->LoadShaderFile(L"../Output/Client/x64/Debug/deferred_ps.cso");
}

void StaticMeshComponent::Load2(void)
{
	staticMesh = std::make_shared<StaticMesh>();
	staticMesh->Load("Plane");

	texture2D = std::make_shared<Texture2D>();
	texture2D->Load("uv_checker");

	//_Shader = std::make_shared<D3D11Shader>();
	//_Shader->Load("Resource/Primitive2.hlsl");

	deferredVertexShader = std::make_shared<VertexShader>(D3D11RHI::Device(), D3D11RHI::Context());
	deferredVertexShader->LoadShaderFile(L"../Output/Client/x64/Debug/deferred_vs.cso");

	deferredPixelShader = std::make_shared<PixelShader>(D3D11RHI::Device(), D3D11RHI::Context());
	deferredPixelShader->LoadShaderFile(L"../Output/Client/x64/Debug/deferred_ps.cso");
}

void StaticMeshComponent::Load3(void)
{
	staticMesh = std::make_shared<StaticMesh>();
	staticMesh->Load("Plane");

	texture2D = std::make_shared<Texture2D>();
	texture2D->Load("uv_checker");

	deferredVertexShader = std::make_shared<VertexShader>(D3D11RHI::Device(), D3D11RHI::Context());
	deferredVertexShader->LoadShaderFile(L"../Output/Client/x64/Debug/deferred_vs.cso");

	deferredPixelShader = std::make_shared<PixelShader>(D3D11RHI::Device(), D3D11RHI::Context());
	deferredPixelShader->LoadShaderFile(L"../Output/Client/x64/Debug/deferred_ps.cso");
}

void StaticMeshComponent::OnUpdate(void)
{
}

void StaticMeshComponent::OnDraw(void)
{
	XMFLOAT4X4 world, view, proj;
	XMStoreFloat4x4(&world, GetOwner()->GetWorldMatrix());
	XMStoreFloat4x4(&view, XMMatrixTranspose(GetOwner()->GetActiveCamera()->GetView()));
	XMStoreFloat4x4(&proj, XMMatrixTranspose(GetOwner()->GetActiveCamera()->GetPerspective()));
	
	for (unsigned int i = 0; i < staticMesh->GetSectionSize(); ++i)
	{
		staticMesh->Draw(i);
		texture2D->Draw(i);
		
		deferredVertexShader->SetMatrix4x4("world", world);
		deferredVertexShader->SetMatrix4x4("view", view);
		deferredVertexShader->SetMatrix4x4("projection", proj);
		deferredVertexShader->CopyAllBufferData();
		deferredVertexShader->SetShader();
		
		deferredPixelShader->SetSamplerState("Sampler", D3D11RHI::Sampler());
		deferredPixelShader->SetShaderResourceView("Texture", texture2D->GetShaderResourceView());
		deferredPixelShader->CopyAllBufferData();
		deferredPixelShader->SetShader();
		
		D3D11RHI::Context()->DrawIndexed(staticMesh->GetIndicesSize(i), 0, 0);
	}
}

void StaticMeshComponent::OnDestroy(void)
{
}


