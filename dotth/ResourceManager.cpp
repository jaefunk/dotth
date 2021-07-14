
#include "ResourceManager.h"
#include "json/json.hpp"
#include "Utility.h"
#include <filesystem>

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
	
	for (auto const& file : j)
	{
		auto path =  "Resource/" + file.get<std::string>();
		auto filesystem = std::filesystem::path(path);
		auto filename = filesystem.filename().u8string();
		auto extension = filesystem.extension().u8string();
		auto key = Utility::Str::Replace(filename, extension, "");
		auto asset = LoadAsset(path);
		decltype(_Resources)::iterator iterator = _Resources.find(key);
		if (asset == nullptr || iterator != _Resources.end())
			return false;
		_Resources.insert(std::make_pair(key, asset));
	}
	return true;
}

std::shared_ptr<AssetBase> ResourceManager::LoadAsset(const std::string& path)
{
	std::shared_ptr<AssetBase> asset;

	if (path.find(".jpg") != std::string::npos)
	{
		asset = std::make_shared<texture>();
		asset->Load(ASSET_TYPE::JPEG, path);
	}
	else if (path.find(".fbx") != std::string::npos || path.find(".FBX") != std::string::npos)
	{
		asset = std::make_shared<model>();
		asset->Load(ASSET_TYPE::FBX, path);
	}
	return asset;
}