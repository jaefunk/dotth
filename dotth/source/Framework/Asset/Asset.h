#pragma once

#include "Framework/Base.h"

enum class ASSET_TYPE {
	NONE,
	BINARY,
	TEXT,	
	TEXTURE,
	MODEL,
	ANIMATION,
};

class Asset : public Base
{
protected:
	ASSET_TYPE _Type = ASSET_TYPE::NONE;
	std::string _Path;

public:
	Asset(const ASSET_TYPE& type) : _Type(type) 
	{
	}
	bool ReadBinary(const char* path, void** data, size_t& size)
	{
		_Path = path;
		
		FILE* file;
		fopen_s(&file, path, "rb");
		fseek(file, 0, SEEK_END);
		size = ftell(file);
		fseek(file, 0, SEEK_SET);
		(*data) = malloc(size);
		memset((*data), 0, size);
		fread((*data), size, 1, file);
		fclose(file);

		return true;
	}

	bool Load(const char* path)
	{
		size_t size = 0;
		void* data = nullptr;
		if (ReadBinary(path, &data, size))
		{
			OnLoad(data, size);
			free(data);
		}
		return true;
	}

	const ASSET_TYPE GetType(void)
	{
		return _Type;
	}
	
private:
	virtual bool OnLoad(void* data, size_t size) = 0;

public:
	virtual void CloneTo(std::shared_ptr<Asset> dst) {}
	virtual void Release(void) {}
};

//////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Utility/SingleInstance.h"

class AssetManager : public SingleInstance<AssetManager>
{
private:
	std::unordered_map<std::string, std::shared_ptr<Asset>> _Assets;

public:
	bool LoadAsset(ASSET_TYPE type, const char* key, const char* path);
	std::shared_ptr<Asset> FindOrigin(const std::string& key);
	std::shared_ptr<Asset> GetClone(const std::string& key)
	{
		return nullptr;
	}
};