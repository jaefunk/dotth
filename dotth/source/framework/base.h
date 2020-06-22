#pragma once

#include "dotth.h"

class noncopyable
{
protected:
	noncopyable(void) = default;
	virtual ~noncopyable(void) = default;
private:
	noncopyable(const noncopyable&) = delete;
	const noncopyable& operator=(const noncopyable&) = delete;
};

class base : private noncopyable
{
private:
	unsigned int _serial;
	std::string _name;
	
public:
	base(void);
	const unsigned int& serial(void) const;
	void name(const std::string& name);
	const std::string& name(void);
};