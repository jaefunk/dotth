
#include "ResourceManager.h"
#include "json/json.hpp"
#include "Utility.h"

#include "Texture2D.h"
#include "StaticMesh.h"

bool ResourceManager2::Load(void)
{
	for (auto& iterator : std::filesystem::recursive_directory_iterator("Resource/"))
	{
		if (!iterator.is_directory())
		{
			auto path = iterator.path();
			auto pathString = path.u8string();
			pathString = Utility::Str::Replace(pathString, "\\", "/");
			auto filesystem = std::filesystem::path(pathString);
			auto filename = filesystem.filename().u8string();
			auto extension = filesystem.extension().u8string();
			auto key = Utility::Str::Replace(filename, extension, "");
			auto loaded = LoadAsset(pathString);
			if (loaded == nullptr)
			{
				std::cout << " ### " << path << " load failed!" << std::endl;
				continue;
			}
			decltype(resources)::iterator find = resources.find(key);
			if (find != resources.end())
			{
				std::cout << " ### " << path << " duplicate file name!" << std::endl;
				continue;
			}
			std::cout << " ### " << path << " was loaded!" << std::endl;
			resources.emplace(std::make_pair(key, loaded));
		}
	}

	return true;
}

std::shared_ptr<Resource> ResourceManager2::LoadAsset(const std::string& path)
{
	if (path.find(".fbx") != std::string::npos)
		return FBXLoader::Load(path);

	if (path.find(".FBX") != std::string::npos)
		return FBXLoader::Load(path);

	if (path.find(".jpg") != std::string::npos)
		return JPEGLoader::Load(path);

	return nullptr;
}