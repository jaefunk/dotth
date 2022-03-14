
#include "SkeletalMesh.h"
#include "ResourceManager.h"

bool SkeletalMesh::Load(const std::string& key)
{
	raw = FBXLoader::Load(key);
	
	if (raw == nullptr)
		return false;

	renderables.clear();
	materials.clear();
	for (auto mesh : raw->meshes)
	{
		renderables.push_back(new Renderable(mesh));
		materials.push_back(new Material);
	}
	return true;
}

void SkeletalMesh::Draw(void)
{
	size_t renderableSize = renderables.size();
	
	Material* mat = nullptr;
	for (size_t index = 0; index < renderableSize; ++index)
	{
		materials[index]->Bind(parameters[index]);
		renderables[index]->Draw();
	}
}
