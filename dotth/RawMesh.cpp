#include "RawMesh.h"
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
#include "libjpeg/include/jpeglib.h"
#include <setjmp.h>
#pragma comment(lib, "libjpeg/lib/libjpeg_a.lib")

unsigned int section::GetVerticeByteWidth(void) const
{
	return static_cast<unsigned int>(sizeof(decltype(vertices)::value_type) * vertices.size());
}
unsigned int section::GetIndiceByteWidth(void) const
{
	return static_cast<unsigned int>(sizeof(decltype(indices)::value_type) * indices.size());
}

class JpegLoader
{
public:
	struct ImageInfo
	{
		uint32_t nWidth;
		uint32_t nHeight;
		uint8_t nNumComponent;
		uint8_t* pData;
	};

	JpegLoader()
	{
		m_pImageInfo = NULL;
	}
	~JpegLoader()
	{
		Cleanup();
	}

	const ImageInfo* Load(const char* szFileName)
	{
		Cleanup();

		jpeg_decompress_struct cinfo;
		ErrorManager errorManager;
		FILE* pFile;
		fopen_s(&pFile, szFileName, "rb");
		//FILE* pFile = fopen(szFileName, "rb");
		if (!pFile)
			return NULL;

		// set our custom error handler
		cinfo.err = jpeg_std_error(&errorManager.defaultErrorManager);
		errorManager.defaultErrorManager.error_exit = ErrorExit;
		errorManager.defaultErrorManager.output_message = OutputMessage;
		if (setjmp(errorManager.jumpBuffer))
		{
			// We jump here on errorz
			Cleanup();
			jpeg_destroy_decompress(&cinfo);
			fclose(pFile);
			return NULL;
		}

		jpeg_create_decompress(&cinfo);
		jpeg_stdio_src(&cinfo, pFile);
		jpeg_read_header(&cinfo, TRUE);
		jpeg_start_decompress(&cinfo);

		m_pImageInfo = new ImageInfo();
		m_pImageInfo->nWidth = cinfo.image_width;
		m_pImageInfo->nHeight = cinfo.image_height;
		m_pImageInfo->nNumComponent = cinfo.num_components;
		m_pImageInfo->pData = new uint8_t[m_pImageInfo->nWidth * m_pImageInfo->nHeight * m_pImageInfo->nNumComponent];

		while (cinfo.output_scanline < cinfo.image_height)
		{
			uint8_t* p = m_pImageInfo->pData + cinfo.output_scanline * cinfo.image_width * cinfo.num_components;
			jpeg_read_scanlines(&cinfo, &p, 1);
		}

		jpeg_finish_decompress(&cinfo);
		jpeg_destroy_decompress(&cinfo);
		fclose(pFile);

		return m_pImageInfo;
	}

private:
	ImageInfo* m_pImageInfo;
	void Cleanup()
	{
		if (m_pImageInfo)
		{
			delete[] m_pImageInfo->pData;
			delete m_pImageInfo;
			m_pImageInfo = NULL;
		}
	}

	struct ErrorManager
	{
		jpeg_error_mgr defaultErrorManager;
		jmp_buf jumpBuffer;
	};

	static void ErrorExit(j_common_ptr cinfo)
	{
		// cinfo->err is actually a pointer to my_error_mgr.defaultErrorManager, since pub
		// is the first element of my_error_mgr we can do a sneaky cast
		ErrorManager* pErrorManager = (ErrorManager*)cinfo->err;
		(*cinfo->err->output_message)(cinfo); // print error message (actually disabled below)
		longjmp(pErrorManager->jumpBuffer, 1);
	}
	static void OutputMessage(j_common_ptr cinfo)
	{
		// disable error messages
		/*char buffer[JMSG_LENGTH_MAX];
		(*cinfo->err->format_message) (cinfo, buffer);
		fprintf(stderr, "%s\n", buffer);*/
	}
};


bool texture::Load(const std::string& path)
{
	JpegLoader loader;
	auto info =loader.Load(path.c_str());
	
	//info->nHeight;
	//info->nWidth;
	//info->nNumComponent;
	//info->pData;
	return false;
}

bool model::LoadWithAssimp(const std::string& path)
{
	Assimp::Importer importer;
	auto scene = importer.ReadFile(path, aiProcess_ConvertToLeftHanded | aiProcess_Triangulate | aiProcess_OptimizeMeshes);
	if (scene == nullptr)
		return false;

	sections.resize(scene->mNumMeshes);
	for (unsigned int index = 0; index < scene->mNumMeshes; ++index)
	{
		auto mesh = scene->mMeshes[index];
		sections[index].vertices.resize(mesh->mNumVertices);
		for (unsigned int i = 0; i < mesh->mNumVertices; ++i)
		{
			if (mesh->HasPositions())
			{
				sections[index].vertices[i].position.x = mesh->mVertices[i].x;
				sections[index].vertices[i].position.y = mesh->mVertices[i].y;
				sections[index].vertices[i].position.z = mesh->mVertices[i].z;
			}

			if (mesh->HasNormals())
			{
				sections[index].vertices[i].normal.x = mesh->mNormals[i].x;
				sections[index].vertices[i].normal.y = mesh->mNormals[i].y;
				sections[index].vertices[i].normal.z = mesh->mNormals[i].z;
			}

			if (mesh->HasTangentsAndBitangents())
			{
				sections[index].vertices[i].tangent.x = mesh->mTangents[i].x;
				sections[index].vertices[i].tangent.y = mesh->mTangents[i].y;
				sections[index].vertices[i].tangent.z = mesh->mTangents[i].z;
			}

			if (mesh->HasTangentsAndBitangents())
			{
				sections[index].vertices[i].bitangent.x = mesh->mBitangents[i].x;
				sections[index].vertices[i].bitangent.y = mesh->mBitangents[i].y;
				sections[index].vertices[i].bitangent.z = mesh->mBitangents[i].z;
			}

			if (mesh->HasTextureCoords(0))
			{
				sections[index].vertices[i].textureCoord.x = mesh->mTextureCoords[0][i].x;
				sections[index].vertices[i].textureCoord.y = mesh->mTextureCoords[0][i].y;
			}

			if (mesh->HasVertexColors(0))
			{
				sections[index].vertices[i].color.r = mesh->mColors[0][i].r;
				sections[index].vertices[i].color.g = mesh->mColors[0][i].g;
				sections[index].vertices[i].color.b = mesh->mColors[0][i].b;
				sections[index].vertices[i].color.a = mesh->mColors[0][i].a;
			}
		}

		if (mesh->HasFaces())
			sections[index].indices.resize(mesh->mNumFaces * 3);
		for (unsigned int i = 0; i < mesh->mNumFaces; ++i)
		{
			unsigned int current = i * 3;
			sections[index].indices[current + 0] = mesh->mFaces[i].mIndices[0];
			sections[index].indices[current + 1] = mesh->mFaces[i].mIndices[1];
			sections[index].indices[current + 2] = mesh->mFaces[i].mIndices[2];
		}
	}
	return true;
}