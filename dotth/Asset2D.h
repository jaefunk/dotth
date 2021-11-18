#pragma once

#include "AssetBase.h"

struct R8G8B8A8 {
	union {
		struct {
			unsigned char R, G, B, A;
		};
		struct {
			unsigned int Alignment;
		};
	};
	
	R8G8B8A8(void) : Alignment(0)
	{

	}
	
	R8G8B8A8(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha)
		: R(red), G(green), B(blue), A(alpha)
	{
	}
};

class Texture : public Resource
{
public:
	virtual std::shared_ptr<Resource> Clone(void) override
	{
		auto p = std::make_shared<Texture>();
		p->ComponentCount = this->ComponentCount;
		p->Width = this->Width;
		p->Height = this->Height;
		p->Texels = this->Texels;
		return p;
	}

public:
	unsigned int ComponentCount;
	unsigned int Width;
	unsigned int Height;
	std::vector<R8G8B8A8> Texels;

public:
	void* GetSysMem(void)
	{
		return static_cast<void*>(Texels.data());
	}
	unsigned int GetSysMemPitch(void)
	{
		return Width * static_cast<unsigned int>(sizeof(R8G8B8A8));
	}
};

class JPEGLoader
{
public:
	static std::unique_ptr<Texture> Load(const std::string& filePath);
};