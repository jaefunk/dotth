#pragma once

#include "SingleInstance.h"
#include "Texture2D.h"
#include "StaticMesh.h"

class ResourceManager2 : public SingleInstance<ResourceManager2>
{
private:
	std::map<std::string, std::unique_ptr<Resource>> resources;

public:
	bool Load(const std::string& reserved);

	template <typename ty>
	static std::shared_ptr<ty> Find(const std::string& key);

private:
	std::unique_ptr<Resource> LoadAsset(const std::string& path)
	{
		if (path.find(".fbx") != std::string::npos || path.find(".FBX") != std::string::npos)
			return FBXLoader::Load(path);
		if (path.find(".jpg") != std::string::npos)
			return JPEGLoader::Load(path);
		return nullptr;
	}
};

template<typename ty>
std::shared_ptr<ty> ResourceManager2::Find(const std::string& key)
{
	auto iter = ResourceManager2::Instance()->resources.find(key);
	if (iter != ResourceManager2::Instance()->resources.end())
		return std::dynamic_pointer_cast<ty>(iter->second->Clone());
	return nullptr;
}
