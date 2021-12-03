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
	staticMesh->Load("Sphere");

	auto texture2D = std::make_shared<Texture2D>();
	texture2D->Load("uv_checker");
	material->SetTexture(texture2D);

	auto deferredVertexShader = std::make_shared<VertexShader>(D3D11RHI::Device(), D3D11RHI::Context());
	deferredVertexShader->LoadShaderFile(L"../Output/Client/x64/Debug/deferred_vs.cso");
	material->SetVertexShader(deferredVertexShader);

	auto deferredPixelShader = std::make_shared<PixelShader>(D3D11RHI::Device(), D3D11RHI::Context());
	deferredPixelShader->LoadShaderFile(L"../Output/Client/x64/Debug/deferred_ps.cso");
	material->SetPixelShader(deferredPixelShader);
}

void StaticMeshComponent::Load2(void)
{
	staticMesh->Load("Plane");

	auto texture2D = std::make_shared<Texture2D>();
	texture2D->Load("uv_checker");

	//_Shader = std::make_shared<D3D11Shader>();
	//_Shader->Load("Resource/Primitive2.hlsl");

	auto deferredVertexShader = std::make_shared<VertexShader>(D3D11RHI::Device(), D3D11RHI::Context());
	deferredVertexShader->LoadShaderFile(L"../Output/Client/x64/Debug/deferred_vs.cso");

	auto deferredPixelShader = std::make_shared<PixelShader>(D3D11RHI::Device(), D3D11RHI::Context());
	deferredPixelShader->LoadShaderFile(L"../Output/Client/x64/Debug/deferred_ps.cso");

	material->SetTexture(texture2D);
	material->SetVertexShader(deferredVertexShader);
	material->SetPixelShader(deferredPixelShader);
}

void StaticMeshComponent::Load3(void)
{
	staticMesh->Load("Plane");

	auto texture2D = std::make_shared<Texture2D>();
	texture2D->Load("uv_checker");
	material->SetTexture(texture2D);

	auto deferredVertexShader = std::make_shared<VertexShader>(D3D11RHI::Device(), D3D11RHI::Context());
	deferredVertexShader->LoadShaderFile(L"../Output/Client/x64/Debug/deferred_vs.cso");
	material->SetVertexShader(deferredVertexShader);

	auto deferredPixelShader = std::make_shared<PixelShader>(D3D11RHI::Device(), D3D11RHI::Context());
	deferredPixelShader->LoadShaderFile(L"../Output/Client/x64/Debug/deferred_ps.cso");
	material->SetPixelShader(deferredPixelShader);
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
		material->Bind(world, view, proj);
		staticMesh->Draw(i);		
	}
}

void StaticMeshComponent::OnDestroy(void)
{
}


