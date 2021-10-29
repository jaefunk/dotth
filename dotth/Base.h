#pragma once

#include "dotth.h"

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
	unsigned int Serial;
	std::string Name;
	
public:
	Base(void);
	virtual ~Base(void);
	unsigned int GetSerial(void) const;
	std::string GetName(void) const;
	void Rename(const std::string& name);
};