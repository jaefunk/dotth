#pragma once

#include "dotth.h"

class Shader {
public:
	virtual bool Load(const char* FileName) = 0;
	virtual void Draw(const Matrix& matrix, unsigned int size) = 0;
};