#include "utility.hpp"

#pragma warning(disable : 4996)
std::string dotth::utility::string::format(const char * format, ...)
{
	va_list args;
	va_start(args, format);
	va_list temp_args;
	va_copy(temp_args, args);
	int size = vsnprintf(nullptr, 0, format, temp_args);
	va_end(temp_args);
	if (size < 0) return "";
	std::string result;
	result.resize(size);
	vsprintf(&(result[0]), format, args);
	va_end(args);
	return result;
}
