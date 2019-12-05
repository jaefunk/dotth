#include "path.hpp"

const std::string dotth::path(std::string path)
{
#ifdef WIN32
	return std::string("../../") + path;
#else
	return path;
#endif
}
