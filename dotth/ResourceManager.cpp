
#include "ResourceManager.h"
#include "json/json.hpp"
#include "Utility.h"

bool ResourceManager::Initialize(void)
{
	_Resources.clear();

	return true;
}

bool ResourceManager::Load(const std::string& reserved)
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

	using namespace nlohmann;
	const json& j = json::parse(read);

	{
		for (auto& p : std::filesystem::recursive_directory_iterator("Resource/"))
		{
			if (p.is_directory())
			{

			}
			else
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
				decltype(_Resources)::iterator iterator = _Resources.find(key);
				if (iterator != _Resources.end())
				{
					std::cout << " ### " << path << " duplicate file name!" << std::endl;
					continue;
				}
				std::cout << path << std::endl;
				_Resources.insert(std::make_pair(key, asset));
			}
		}
	}

	return true;
}

std::shared_ptr<AssetBase> ResourceManager::LoadAsset(const std::string& path)
{
	std::shared_ptr<AssetBase> asset;

	if (path.find(".jpg") != std::string::npos)
		asset = std::make_shared<TextureBase>();
	else if (path.find(".fbx") != std::string::npos || path.find(".FBX") != std::string::npos)
		asset = std::make_shared<ModelBase>();

	return asset != nullptr ? (asset->Load(path) ? asset : nullptr) : nullptr;
}