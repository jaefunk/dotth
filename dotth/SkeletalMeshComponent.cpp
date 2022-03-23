#include "SkeletalMeshComponent.h"
#include "Camera.h"


void SkeletalMeshComponent::OnInit(void)
{	
}

void SkeletalMeshComponent::OnUpdate(void)
{
}

void SkeletalMeshComponent::OnDraw(void)
{	
	dotth::matrix world = GetOwner()->GetWorldMatrix();
	dotth::matrix view = GetOwner()->GetActiveCamera()->GetView();
	dotth::matrix proj = GetOwner()->GetActiveCamera()->GetProjection();

	std::vector<MeshRenderParameter> parameters;
	parameters.push_back(MeshRenderParameter({ "world", &world, sizeof(world) }));
	parameters.push_back(MeshRenderParameter({ "view", &view, sizeof(view) }));
	parameters.push_back(MeshRenderParameter({ "proj", &proj, sizeof(proj) }));
	parameters.push_back(MeshRenderParameter({ "bones", finalMatrixes.data(), static_cast<unsigned int>(finalMatrixes.size() * sizeof(dotth::matrix)) }));

	skeletalMesh->SetVertexParameters(0, parameters);
	skeletalMesh->SetVertexParameters(1, parameters);
	skeletalMesh->Draw();
}

void SkeletalMeshComponent::OnDestroy(void)
{
}

