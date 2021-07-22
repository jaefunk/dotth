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

class TextureBase : public AssetBase 
{
public:
	unsigned int ComponentCount;
	unsigned int Width;
	unsigned int Height;
	std::vector<R8G8B8A8> Texels;

public:
	virtual bool Load(const std::string& path) override;	

public:
	void* GetSysMem(void);
	unsigned int GetSysMemPitch(void);

private:
	bool LoadJpeg(const std::string& path);
};