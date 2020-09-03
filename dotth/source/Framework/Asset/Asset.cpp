
#include "Framework/Asset/Asset.h"
#include "Framework/Asset/Asset_Texture.h"
#include "Framework/Asset/Asset_Model.h"

bool AssetManager::LoadAsset(ASSET_TYPE type, const char* key, const char* path)
{
	std::shared_ptr<Asset> asset;
	switch (type)
	{
	case ASSET_TYPE::TEXTURE: 
		asset = std::make_shared<Asset_Texture>(); 
		break;
	case ASSET_TYPE::MODEL: 
		asset = std::make_shared<Asset_Model>(); 
		break;
	default:
		break;
	}

	if (asset == nullptr)
		return false;
	asset->Load(path);
	_Assets.insert({ key, asset });

	return true;
}

std::shared_ptr<Asset> AssetManager::FindOrigin(const std::string & key)
{
	auto iter = _Assets.find(key);
	if (iter == _Assets.end())
		return nullptr;
	return iter->second;
}
