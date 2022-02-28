
#include "SkeletalMesh.h"
#include "ResourceManager.h"

bool SkeletalMesh::Load(const std::string& key)
{
	Raw = FBXLoader::Load(key);
	if (Raw == nullptr)
		return false;

	for (auto mesh : Raw->meshes)
	{
		Renderables.push_back(new Renderable(mesh));
	}
	return true;
}

void SkeletalMesh::Draw(unsigned int index)
{
	Renderables[index]->Draw();
}
