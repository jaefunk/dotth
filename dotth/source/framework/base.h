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
	int _serial;
	std::time_t _birth;
public:
	base(void);
	const int& serial(void) const;
	const std::time_t& birth(void) const;
};