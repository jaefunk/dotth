#pragma once

#include "Framework/Base.h"

enum class ASSET_TYPE {
	NONE,
	TEXT,
	BINARY,
	TEXTURE2D,
	MODEL,
	ANIMATION,
};

class Asset : public Base
{
protected:
	ASSET_TYPE _Type = ASSET_TYPE::NONE;
	std::string _FilePath;

public:
	Asset(const ASSET_TYPE& type) : _Type(type) 
	{
	}
	bool Load(const std::string FilePath)
	{
		_FilePath = FilePath;

		FILE* file;
		fopen_s(&file, FilePath.c_str(), "r");
		fseek(file, 0, SEEK_END);
		auto length = ftell(file);
		fseek(file, 0, SEEK_SET);
		char* data = new char[length];
		fread(data, 1, length, file);
		fclose(file);

		OnLoad(data, length);

		delete[] data;

		return true;
	}
	const ASSET_TYPE GetType(void)
	{
		return _Type;
	}
	
private:
	virtual bool OnLoad(const char* data, long length) = 0;

public:
	virtual void CloneTo(Asset* dst) {}
	virtual void Release(void) {}
};