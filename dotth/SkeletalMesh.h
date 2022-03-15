#pragma once

#include "Renderable.h"
#include "Material.h"

class SkeletalMesh
{
public:
	std::shared_ptr<dotth::model> raw;
	std::vector<Renderable*> renderables;
	std::vector<Material*> materials;

public:
	std::map<int, std::vector<MeshRenderParameter>> parameters;
	bool Load(const std::string& key);

public:
	void SetVertexParameters(unsigned int index, const std::vector<MeshRenderParameter>& inParameters)
	{
		parameters[index] = inParameters;
	}

	void Draw(void);
};