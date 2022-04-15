
#include "StaticMesh.h"
#include "ResourceManager.h"

bool StaticMesh::Load(const std::string& key)
{
	raw = FBXLoader::Load(key);

	if (raw == nullptr)
		return false;
	
	Load(raw);

	return true;
}

bool StaticMesh::Load(const std::shared_ptr<dotth::model> model)
{
	renderables.clear();
	materials.clear();

	for (auto mesh : model->meshes)
	{
		renderables.push_back(new Renderable(mesh));
		materials.push_back(new Material);
	}
	return true;
}

void StaticMesh::Draw(void)
{
	size_t renderableSize = renderables.size();

	Material* mat = nullptr;
	for (size_t index = 0; index < renderableSize; ++index)
	{
		materials[index]->Bind(parameters[index]);
		renderables[index]->Draw();
	}
}
