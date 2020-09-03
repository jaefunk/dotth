#pragma once

#include "Framework/Asset/Asset.h"

class Asset_Text : public Asset
{
private:
	std::string _String;

public:
	Asset_Text(void) : Asset(ASSET_TYPE::TEXT)
	{
	}

private:
	virtual bool OnLoad(void* data, size_t size) override
	{
		_String.assign((char*)data);
		return true;
	}
};