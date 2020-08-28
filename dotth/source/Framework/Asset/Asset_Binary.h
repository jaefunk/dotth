#pragma once

#include "Framework/Asset/Asset.h"

class Asset_Binary : public Asset
{
private:
	std::vector<char> _Data;

public:
	Asset_Binary(void) : Asset(ASSET_TYPE::BINARY)
	{
	}

private:
	virtual bool OnLoad(const char* data, long length) override
	{
		_Data.assign(length, 0);
		memcpy(_Data.data(), data, length);
		return true;
	}
};