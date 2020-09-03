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
	virtual bool OnLoad(void* data, size_t size) override
	{
		_Data.assign(size, 0);
		memcpy(_Data.data(), data, size);
		return true;
	}
};