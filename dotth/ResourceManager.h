#pragma once

#include "SingleInstance.h"
#include "Texture2D.h"
#include "StaticMesh.h"

class ResourceManager : public SingleInstance<ResourceManager>
{
private:
	std::map<std::string, std::shared_ptr<AssetBase>> _Resources;

public:
	bool Initialize(void);
	bool Load(const std::string& reserved);

	template <typename ty>
	static std::shared_ptr<ty> Find(const std::string& key);

private:
	std::shared_ptr<AssetBase> LoadAsset(const std::string& path);
};

template<typename ty>
std::shared_ptr<ty> ResourceManager::Find(const std::string& key)
{
	auto iter = ResourceManager::Instance()->_Resources.find(key);
	if (iter != ResourceManager::Instance()->_Resources.end())
		return std::dynamic_pointer_cast<ty>(iter->second);
	return nullptr;
}
