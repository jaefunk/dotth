#pragma once

#include "SingleInstance.h"
#include "AssetBase.h"

class ResourceManager2 : public SingleInstance<ResourceManager2>
{
private:
	std::map<std::string, std::shared_ptr<Resource>> resources;

public:
	bool Load(void);

	template <typename ty>
	static std::shared_ptr<ty> Find(const std::string& key);

private:
	std::shared_ptr<Resource> LoadAsset(const std::string& path);
};

template<typename ty>
std::shared_ptr<ty> ResourceManager2::Find(const std::string& key)
{
	auto iter = ResourceManager2::Instance()->resources.find(key);
	if (iter != ResourceManager2::Instance()->resources.end())
		return std::dynamic_pointer_cast<ty>(iter->second);
	return nullptr;
}
