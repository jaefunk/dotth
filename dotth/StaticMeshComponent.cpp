#include "StaticMeshComponent.h"
#include "Camera.h"

void StaticMeshComponent::OnInit(void)
{		
}

void StaticMeshComponent::OnUpdate(void)
{
}

void StaticMeshComponent::OnDraw(void)
{
	dotth::matrix world = GetOwner()->GetWorldMatrix();
	dotth::matrix view = GetOwner()->GetActiveCamera()->GetView();
	dotth::matrix proj = GetOwner()->GetActiveCamera()->GetProjection();

	std::vector<MeshRenderParameter> parameters;
	parameters.push_back(MeshRenderParameter({ "world", &world, sizeof(world) }));
	parameters.push_back(MeshRenderParameter({ "view", &view, sizeof(view) }));
	parameters.push_back(MeshRenderParameter({ "proj", &proj, sizeof(proj) }));

	staticMesh->SetVertexParameters(0, parameters);
	staticMesh->SetVertexParameters(1, parameters);
	staticMesh->Draw();
}

void StaticMeshComponent::OnDestroy(void)
{
}

