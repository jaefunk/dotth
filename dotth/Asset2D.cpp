
#include "Asset2d.h"

#include "libjpeg/include/jpeglib.h"
#include <setjmp.h>
#pragma comment(lib, "libjpeg/lib/libjpeg_a.lib")

bool TextureBase::Load(const std::string& path)
{
	std::filesystem::path fs(path);
	std::string extension = fs.extension().u8string();
	if (extension == ".jpg" || extension == ".JPG" || extension == ".jpeg" || extension == ".JPEG")
		return LoadJpeg(path);
	return false;
}

bool TextureBase::LoadJpeg(const std::string& path)
{
	jpeg_error_mgr error_msg;
	error_msg.error_exit = [](j_common_ptr cinfo) {};
	error_msg.output_message = [](j_common_ptr cinfo) {};

	FILE* pFile;
	fopen_s(&pFile, path.c_str(), "rb");
	if (!pFile)
		return false;

	jpeg_decompress_struct cinfo;
	cinfo.err = jpeg_std_error(&error_msg);
	
	jmp_buf jumpBuffer;
	if (setjmp(jumpBuffer))
	{
		jpeg_destroy_decompress(&cinfo);
		fclose(pFile);
		return false;
	}

	jpeg_create_decompress(&cinfo);
	jpeg_stdio_src(&cinfo, pFile);
	jpeg_read_header(&cinfo, TRUE);
	jpeg_start_decompress(&cinfo);

	Width = cinfo.image_width;
	Height = cinfo.image_height;
	ComponentCount = cinfo.num_components;

	unsigned int ByteSize = cinfo.output_width * cinfo.output_height * ComponentCount;
	unsigned char* pData = new unsigned char[ByteSize];

	unsigned char* position = pData;
	while (cinfo.output_scanline < cinfo.image_height)
	{
		jpeg_read_scanlines(&cinfo, &position, 1);
		int address = cinfo.output_width * cinfo.output_components;
		position += address;
	}

	int distance = 0;
	unsigned int Area = Width * Height;
	Texels.resize(Area);
	for (unsigned int index = 0; index < Width * Height; ++index)
	{
		Texels[index].R = pData[distance + 0];
		Texels[index].G = pData[distance + 1];
		Texels[index].B = pData[distance + 2];
		Texels[index].A = 255;
		distance += cinfo.output_components;
	}

	delete[] pData;
	jpeg_finish_decompress(&cinfo);
	jpeg_destroy_decompress(&cinfo);
	fclose(pFile);

	return true;
}

void* TextureBase::GetSysMem(void)
{
	return static_cast<void*>(Texels.data());
}

unsigned int TextureBase::GetSysMemPitch(void)
{
	return Width * static_cast<unsigned int>(sizeof(R8G8B8A8));
}