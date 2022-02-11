
#include "ResourceManager.h"
#include "json/json.hpp"
#include "Utility.h"

bool ResourceManager2::Load(const std::string& reserved)
{
	std::ifstream file;
	file.open(reserved, std::ios_base::binary);
	std::string read;
	while (file) {
		std::string s;
		getline(file, s);
		read.append(s);
	}
	file.close();

	for (auto& p : std::filesystem::recursive_directory_iterator("Resource/"))
	{
		if (!p.is_directory())
		{
			auto j = p.path();
			auto path = j.u8string();
			path = Utility::Str::Replace(path, "\\", "/");
			auto filesystem = std::filesystem::path(path);
			auto filename = filesystem.filename().u8string();
			auto extension = filesystem.extension().u8string();
			auto key = Utility::Str::Replace(filename, extension, "");
			auto asset = LoadAsset(path);
			if (asset == nullptr)
			{
				std::cout << " ### " << path << " load failed!" << std::endl;
				continue;
			}
			decltype(resources)::iterator iterator = resources.find(key);
			if (iterator != resources.end())
			{
				std::cout << " ### " << path << " duplicate file name!" << std::endl;
				continue;
			}
			std::cout << path << std::endl;
			resources.emplace(std::make_pair(key, std::move(asset)));
		}
	}

	return true;
}

std::shared_ptr<Resource> ResourceManager2::LoadAsset(const std::string& path)
{
	if (path.find(".fbx") != std::string::npos)
		return FBXLoader2::Load(path);

	if (path.find(".FBX") != std::string::npos)
		return FBXLoader2::Load(path);

	if (path.find(".jpg") != std::string::npos)
		return JPEGLoader::Load(path);

	return nullptr;
}
