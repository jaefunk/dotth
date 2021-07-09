
#include "Asset2d.h"

#include "libjpeg/include/jpeglib.h"
#include <setjmp.h>
#pragma comment(lib, "libjpeg/lib/libjpeg_a.lib")

class JpegLoader
{
public:
	struct ImageInfo
	{
		unsigned int nWidth;
		unsigned int nHeight;
		unsigned char nNumComponent;
		unsigned char* pData;
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


bool texture::LoadJpeg(const std::string& path)
{
	jpeg_error_mgr error_msg;
	jmp_buf jumpBuffer;
	

	jpeg_decompress_struct cinfo;
	FILE* pFile;
	fopen_s(&pFile, path.c_str(), "rb");
	if (!pFile)
		return false;

	// set our custom error handler
	cinfo.err = jpeg_std_error(&error_msg);
	error_msg.error_exit = [](j_common_ptr cinfo) {};
	error_msg.output_message = [](j_common_ptr cinfo) {};
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

	width = cinfo.image_width;
	height = cinfo.image_height;
	component_count = cinfo.num_components;
	unsigned char* pData;
	pData = new unsigned char[cinfo.output_width * cinfo.output_height * component_count];
	pData[0] = 10;

	unsigned int counter = 0;
	unsigned char* position = pData;
	while (cinfo.output_scanline < cinfo.image_height)
	{
		jpeg_read_scanlines(&cinfo, &position, 1);
		position += cinfo.output_width * cinfo.output_components;
	}

	int distance = 0;
	texels.resize(width * height);
	for (int index = 0; index < width * height; ++index)
	{
		texels[index].R = pData[distance++];
		texels[index].G = pData[distance++];
		texels[index].B = pData[distance++];
		texels[index].A = 255;
		/*texels[index].R = pData[distance++];
		texels[index].G = pData[distance++];
		texels[index].B = pData[distance++];
		texels[index].A = 255;*/
	}

	delete[] pData;
	jpeg_finish_decompress(&cinfo);
	jpeg_destroy_decompress(&cinfo);
	fclose(pFile);

	return true;
}