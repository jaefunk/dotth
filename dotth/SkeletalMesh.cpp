
#include "SkeletalMesh.h"
#include "ResourceManager.h"

bool SkeletalMesh::Load(const std::string& key)
{
	std::shared_ptr<dotth::model> loadedModel = FBXLoader::Load(key);
	
	if (loadedModel == nullptr)
		return false;
	raw = loadedModel;
	renderables.clear();
	materials.clear();
	for (auto mesh : loadedModel->meshes)
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
