#pragma once

#include <string>

class NonCopyable
{
protected:
	NonCopyable(void) = default;
	virtual ~NonCopyable(void) = default;
private:
	NonCopyable(const NonCopyable&) = delete;
	const NonCopyable& operator=(const NonCopyable&) = delete;
};

class Base : private NonCopyable
{
private:
	unsigned int serial;
	std::string name;
	
public:
	Base(void);
	unsigned int GetSerial(void) const;
	std::string GetName(void) const;
	void Rename(const std::string& newName);
};