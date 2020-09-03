
#include "ModelComponent.h"



ModelComponent::ModelComponent(const char * asset)
{
	_Model = std::static_pointer_cast<Asset_Model>(AssetManager::Instance()->FindOrigin(asset));
	_Texture = std::static_pointer_cast<Asset_Texture>(AssetManager::Instance()->FindOrigin("robot_t"));
}

void ModelComponent::OnUpdate(void) 
{
}

void ModelComponent::OnDraw(void) 
{
	Renderer::RHI()->BindVertexBuffer(_VertexBuffer, GetVertexStructureSize(), 0);
	Renderer::RHI()->BindIndexBuffer(_IndexBuffer, DXGI_FORMAT_R32_UINT, 0);
	static float f = 0.f;
	MatrixBufferType cb;
	cb.view = DirectX::XMMatrixTranspose(*Camera::Instance()->View());
	cb.projection = DirectX::XMMatrixTranspose(*Camera::Instance()->Perspective());
	auto world = DirectX::XMMatrixRotationY(f);
	f += 0.0003f;
	cb.world = DirectX::XMMatrixTranspose(world);
	Renderer::RHI()->UpdateSubresource(_ConstantBuffer, &cb);
	_Texture->Bind();
	_Shader.Draw(_ConstantBuffer, GetIndexCount());
	
}

void ModelComponent::OnDestroy(void) 
{
}
