
#include "AssetBase.h"
#include "libjpeg/include/jpeglib.h"
#include <setjmp.h>
#pragma comment(lib, "libjpeg/lib/libjpeg_a.lib")

std::shared_ptr<dotth::model> FBXLoader2::Load(const std::string& filePath)
{
	std::shared_ptr<dotth::model> mesh;
	Assimp::Importer importer;
	unsigned int flags = aiProcess_ConvertToLeftHanded | aiProcess_Triangulate | aiProcess_OptimizeMeshes | aiProcess_PopulateArmatureData | aiProcess_LimitBoneWeights;
	auto scene = importer.ReadFile(filePath, flags);
	if (scene == nullptr)
		return mesh;
	mesh = std::make_shared<dotth::model>(scene);
	return mesh;
}

std::unique_ptr<Mesh> FBXLoader::Load(const std::string& filePath)
{
	std::unique_ptr<Mesh> mesh = std::make_unique<Mesh>();
	Assimp::Importer importer;
	unsigned int flags = aiProcess_ConvertToLeftHanded | aiProcess_Triangulate | aiProcess_OptimizeMeshes | aiProcess_PopulateArmatureData | aiProcess_LimitBoneWeights;
	auto scene = importer.ReadFile(filePath, flags);
	if (scene == nullptr)
		return mesh;

	mesh->primitiveNodes.resize(scene->mNumMeshes);
	for (unsigned int index = 0; index < scene->mNumMeshes; ++index)
	{
		auto sceneMesh = scene->mMeshes[index];
		Mesh::PrimitiveNode& node = mesh->primitiveNodes[index];		
		node.vertices.resize(sceneMesh->mNumVertices);
		for (unsigned int i = 0; i < sceneMesh->mNumVertices; ++i)
		{
			if (sceneMesh->HasPositions())
			{
				node.vertices[i].position.x = sceneMesh->mVertices[i].x;
				node.vertices[i].position.y = -sceneMesh->mVertices[i].z;
				node.vertices[i].position.z = sceneMesh->mVertices[i].y;
			}

			if (sceneMesh->HasNormals())
			{
				node.vertices[i].normal.x = sceneMesh->mNormals[i].x;
				node.vertices[i].normal.y = -sceneMesh->mNormals[i].z;
				node.vertices[i].normal.z = sceneMesh->mNormals[i].y;
			}

			if (sceneMesh->HasTangentsAndBitangents())
			{
				node.vertices[i].tangent.x = sceneMesh->mTangents[i].x;
				node.vertices[i].tangent.y = sceneMesh->mTangents[i].y;
				node.vertices[i].tangent.z = sceneMesh->mTangents[i].z;
			}

			if (sceneMesh->HasTangentsAndBitangents())
			{
				node.vertices[i].bitangent.x = sceneMesh->mBitangents[i].x;
				node.vertices[i].bitangent.y = sceneMesh->mBitangents[i].y;
				node.vertices[i].bitangent.z = sceneMesh->mBitangents[i].z;
			}

			if (sceneMesh->HasTextureCoords(0))
			{
				node.vertices[i].textureCoord.x = sceneMesh->mTextureCoords[0][i].x;
				node.vertices[i].textureCoord.y = sceneMesh->mTextureCoords[0][i].y;
			}

			if (sceneMesh->HasVertexColors(0))
			{
				node.vertices[i].color.x = sceneMesh->mColors[0][i].r;
				node.vertices[i].color.y = sceneMesh->mColors[0][i].g;
				node.vertices[i].color.z = sceneMesh->mColors[0][i].b;
				node.vertices[i].color.w = sceneMesh->mColors[0][i].a;
			}
		}

		if (sceneMesh->HasFaces())
		{
			node.indices.resize(static_cast<size_t>(sceneMesh->mNumFaces) * 3);
			for (unsigned int i = 0; i < sceneMesh->mNumFaces; ++i)
			{
				unsigned int current = i * 3;
				node.indices[current++] = sceneMesh->mFaces[i].mIndices[0];
				node.indices[current++] = sceneMesh->mFaces[i].mIndices[1];
				node.indices[current] = sceneMesh->mFaces[i].mIndices[2];
			}
		}

		if (sceneMesh->HasBones())
		{
			for (unsigned int i = 0; i < sceneMesh->mNumBones; ++i)
			{
				sceneMesh->mBones[i]->mArmature;
				sceneMesh->mBones[i]->mName;
				sceneMesh->mBones[i]->mNode;
				sceneMesh->mBones[i]->mNumWeights;
				sceneMesh->mBones[i]->mOffsetMatrix;
				sceneMesh->mBones[i]->mWeights;
			}
		}
	}

	if (scene->HasAnimations())
	{		
		for (unsigned int i = 0; i < scene->mNumAnimations; ++i)
		{
			auto animation = scene->mAnimations[i];
			
		}
	}
	return mesh;
}

std::unique_ptr<Texture> JPEGLoader::Load(const std::string& filePath)
{
	std::unique_ptr<Texture> texture = std::make_unique<Texture>();

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
		texture->Texels[index].R = pData[distance + 0];
		texture->Texels[index].G = pData[distance + 1];
		texture->Texels[index].B = pData[distance + 2];
		texture->Texels[index].A = 255;
		distance += cinfo.output_components;
	}

	delete[] pData;
	jpeg_finish_decompress(&cinfo);
	jpeg_destroy_decompress(&cinfo);
	fclose(pFile);

	return texture;
}