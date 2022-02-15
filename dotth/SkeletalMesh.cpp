
#include "SkeletalMesh.h"
#include "ResourceManager.h"

bool SkeletalMesh::Load(const std::string& key)
{
	Raw = ResourceManager2::Find<dotth::model>(key);
	if (Raw == nullptr)
		return false;

	for (auto index = 0; index < Raw->numMeshes; ++index)
	{
		Renderables.push_back(new Renderable(Raw->meshes[index]));
	}
	return true;
}

void SkeletalMesh::Draw(unsigned int index)
{
	Renderables[index]->Draw();
}
