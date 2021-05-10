
#pragma once

#include "Float2.h"
#include "Float3.h"
#include "Float4.h"
#include "Matrix.h"

struct Transform 
{
protected:
	Vector3F Rotation{ 0.f, 0.f, 0.f };
	Vector3F Translation{ 0.f, 0.f, 0.f };
	Vector3F Scale3D{ 1.f, 1.f, 1.f };

public:
	
};