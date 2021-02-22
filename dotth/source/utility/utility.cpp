#include "Utility.h"

#pragma warning(disable : 4996)
std::string Utility::Str::Format(const char * format, ...)
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

std::vector<std::string> Utility::Str::Split(std::string src, std::string token)
{
	if (token.length() == 0 || src.find(token) == std::string::npos)
		return std::vector<std::string>({ src });

	std::vector<std::string> result;
	std::size_t offset = 0;
	std::size_t split = 0;
	while ((split = src.find(token, offset)) != std::string::npos)
	{
		result.push_back(src.substr(offset, split - offset));
		offset = split + token.length();
	}
	result.push_back(src.substr(offset, src.length() - offset));
	return result;
}

long long Utility::Time::TSE(void)
{
	return std::chrono::system_clock::now().time_since_epoch().count() / 1000;
}
