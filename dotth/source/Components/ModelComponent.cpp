
#include "ModelComponent.h"



ModelComponent::ModelComponent(const char * asset)
{
	_Model = std::static_pointer_cast<Asset_Model>(AssetManager::Instance()->FindOrigin(asset));
	_Texture = std::static_pointer_cast<Asset_Texture>(AssetManager::Instance()->FindOrigin("robot_t"));
}

unsigned int ModelComponent::GetVertexStructureSize(void)
{
	return sizeof(VertexPNU);
}

unsigned int ModelComponent::GetVertexCount(void)
{
	return _Model->_VertexCount;
}

unsigned int ModelComponent::GetIndexCount(void)
{
	return _Model->_IndexCount;
}

void * ModelComponent::GetVertexArray(void)
{
	return _Model->_Meshes[1]._Vertices.data();
}

unsigned long * ModelComponent::GetIndexArray(void)
{
	return _Model->_Meshes[1]._Indices.data();
}

std::string ModelComponent::GetShaderName(void)
{
	return "Resource/Model.fx";
}

void ModelComponent::GetInputDesc(D3D11_INPUT_ELEMENT_DESC ** desc, unsigned int & size)
{
	(*desc) = new D3D11_INPUT_ELEMENT_DESC[2];
	(*desc)[0] = { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 };
	//(*desc)[1] = { "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 };
	(*desc)[1] = { "TEXCOORD0", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 };
	size = 2;
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
