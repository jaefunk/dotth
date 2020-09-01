
#include "ModelComponent.h"

#ifdef max
#undef max
#endif

#ifdef min
#undef min
#endif

#include "assimp/Importer.hpp"
#include "assimp/postprocess.h"
#include "assimp/scene.h"

void ModelComponent::OnInit(void) 
{
	Assimp::Importer importer;

	const aiScene* pScene = importer.ReadFile("", aiProcess_Triangulate | aiProcess_ConvertToLeftHanded);
}

void ModelComponent::OnUpdate(void) 
{
}

void ModelComponent::OnDraw(void) 
{
}

void ModelComponent::OnDestroy(void) 
{
}
