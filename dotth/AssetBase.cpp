
#include "AssetBase.h"
#include <setjmp.h>
#pragma comment(lib, "libjpeg/lib/libjpeg_a.lib")


std::shared_ptr<dotth::model> FBXLoader::Load(const std::string& filePath)
{
	std::shared_ptr<dotth::model> mesh;
	Assimp::Importer importer;
	unsigned int flags = aiProcess_ConvertToLeftHanded | aiProcess_Triangulate | aiProcess_OptimizeMeshes | aiProcess_PopulateArmatureData | aiProcess_LimitBoneWeights;
	auto scene = importer.ReadFile(filePath, flags);
	if (scene == nullptr)
		return mesh;
	mesh = std::make_unique<dotth::model>(scene);

	auto m = new dotth2::model(scene);
	return mesh;
}

std::shared_ptr<dotth2::model> FBXLoader::Load2(const std::string& filePath)
{
	std::shared_ptr<dotth2::model> mesh;
	Assimp::Importer importer;
	unsigned int flags = aiProcess_ConvertToLeftHanded | aiProcess_Triangulate | aiProcess_OptimizeMeshes | aiProcess_PopulateArmatureData | aiProcess_LimitBoneWeights;
	auto scene = importer.ReadFile(filePath, flags);
	if (scene == nullptr)
		return mesh;
	mesh = std::make_shared<dotth2::model>(scene);
	return mesh;
}

std::shared_ptr<Texture> JPEGLoader::Load(const std::string& filePath)
{
	std::shared_ptr<Texture> texture = std::make_shared<Texture>();

	jpeg_error_mgr error_msg;
	error_msg.error_exit = [](j_common_ptr cinfo) {};
	error_msg.output_message = [](j_common_ptr cinfo) {};

	FILE* pFile;
	fopen_s(&pFile, filePath.c_str(), "rb");
	if (!pFile)
		return texture;

	jpeg_decompress_struct cinfo;
	cinfo.err = jpeg_std_error(&error_msg);

	jmp_buf jumpBuffer;
	if (setjmp(jumpBuffer))
	{
		jpeg_destroy_decompress(&cinfo);
		fclose(pFile);
		return texture;
	}

	jpeg_create_decompress(&cinfo);
	jpeg_stdio_src(&cinfo, pFile);
	jpeg_read_header(&cinfo, TRUE);
	jpeg_start_decompress(&cinfo);

	texture->Width = cinfo.image_width;
	texture->Height = cinfo.image_height;
	texture->ComponentCount = cinfo.num_components;

	unsigned int ByteSize = cinfo.output_width * cinfo.output_height * texture->ComponentCount;
	unsigned char* pData = new unsigned char[ByteSize];

	unsigned char* position = pData; 
	while (cinfo.output_scanline < cinfo.image_height)
	{
		jpeg_read_scanlines(&cinfo, &position, 1);
		int address = cinfo.output_width * cinfo.output_components;
		position += address;
	}

	int distance = 0;
	unsigned int Area = texture->Width * texture->Height;
	texture->Texels.resize(Area);
	for (unsigned int index = 0; index < texture->Width * texture->Height; ++index)
	{
		texture->Texels[index].r = pData[distance + 0];
		texture->Texels[index].g = pData[distance + 1];
		texture->Texels[index].b = pData[distance + 2];
		texture->Texels[index].a = 255;
		distance += cinfo.output_components;
	}

	delete[] pData;
	jpeg_finish_decompress(&cinfo);
	jpeg_destroy_decompress(&cinfo);
	fclose(pFile);

	return texture;
}