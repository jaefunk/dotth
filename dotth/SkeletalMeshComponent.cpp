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
	dotth::matrix proj = GetOwner()->GetActiveCamera()->GetPerspective();
	std::vector<SkeletalMeshRenderParameter> parameters;
	parameters.push_back(SkeletalMeshRenderParameter({ "world", &world, sizeof(world) }));
	parameters.push_back(SkeletalMeshRenderParameter({ "view", &view, sizeof(view) }));
	parameters.push_back(SkeletalMeshRenderParameter({ "proj", &proj, sizeof(proj) }));
	parameters.push_back(SkeletalMeshRenderParameter({ "bones", finalMatrixes.data(), static_cast<unsigned int>(finalMatrixes.size() * sizeof(dotth::matrix)) }));
	skeletalMesh->SetVertexParameters(0, parameters);
	skeletalMesh->SetVertexParameters(1, parameters);
	skeletalMesh->Draw();
}

void SkeletalMeshComponent::OnDestroy(void)
{
}

