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
	virtual bool OnLoad(const char* data, long length) override
	{
		_String.assign((char*)data);
		return true;
	}
};