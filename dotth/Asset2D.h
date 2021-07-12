#pragma once

#include "AssetBase.h"

struct r8g8b8a8 {
	unsigned char R, G, B, A;
	r8g8b8a8()
	{

	}
	
	r8g8b8a8(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha)
		:A(alpha), R(red), G(green), B(blue)
	{

		//alignment = blue << 0 | green << 8 | red << 16 | alpha << 24;
	}
};

class texture : public AssetBase 
{
public:
	std::string name;
	unsigned int component_count;
	unsigned int width;
	unsigned int height;
	std::vector<r8g8b8a8> texels;
	virtual bool Load(const ASSET_TYPE& type, const std::string& path) override
	{
		if (type == ASSET_TYPE::JPEG)
			return LoadJpeg(path);
		return false;
	}
private:
	bool LoadJpeg(const std::string& path);
};