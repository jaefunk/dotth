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
	unsigned int _Serial;
	std::string _Name;
	
public:
	Base(void);
	const unsigned int& Serial(void) const;
	void Rename(const std::string& name);
	const std::string& Name(void);
};