
#pragma once

#include "Float2.h"
#include "Float3.h"
#include "Float4.h"
#include "Matrix.h"

struct Transform 
{
protected:
	Vector3F Scale{ 1.f, 1.f, 1.f };
	Vector3F Rotation{ 0.f, 0.f, 0.f };
	Vector3F Position{ 0.f, 0.f, 0.f };

public:
	void SetScale(const Vector3F& value) { Scale = value; }
	void Scaling(const Vector3F& value) { Vector3F::Multiply(Scale, value, Scale); }
	void Scaling(const float& value) { Vector3F::Multiply(Scale, value, Scale); }
	void ScalingX(const float& value) { Scale.x *= value; }
	void ScalingY(const float& value) { Scale.y *= value; }
	void ScalingZ(const float& value) { Scale.z *= value; }
	const Vector3F& GetScale(void) { return Scale; }

	void SetRotation(const Vector3F& value) { Rotation = value; }
	void Rotate(const Vector3F& value) { Vector3F::Add(Rotation, value, Rotation); }
	void RotateAxisX(const float& value) { Rotation.x += value; }
	void RotateAxisY(const float& value) { Rotation.y += value; }
	void RotateAxisZ(const float& value) { Rotation.z += value; }
	const Vector3F& GetRotation(void) { return Rotation; }

	void SetPosition(const Vector3F& value) { Position = value; }
	void Translate(const Vector3F& value) { Vector3F::Add(Position, value, Position); }
	void TranslateX(const float& value) { Position.x += value; }
	void TranslateY(const float& value) { Position.y += value; }
	void TranslateZ(const float& value) { Position.z += value; }
	const Vector3F& GetPosition(void) { return Position; }

	const Matrix& ToMatrix(bool withScale) 
	{
		return withScale ? ToMatrixWithScale() : ToMatrixNoScale();
	}

private:
	Matrix ToMatrixWithScale(void) 
	{ 
		XMMATRIX pos = XMMatrixTranslation(Position.x, Position.y, Position.z);
		XMMATRIX rotx = XMMatrixRotationX(Rotation.x);
		XMMATRIX roty = XMMatrixRotationY(Rotation.y);
		XMMATRIX rotz = XMMatrixRotationZ(Rotation.z);
		XMMATRIX scl = XMMatrixScaling(Scale.x, Scale.y, Scale.z);

		XMMATRIX total = scl * rotz * roty * rotx * pos;
		XMFLOAT4X4 result;
		XMStoreFloat4x4(&result, XMMatrixTranspose(total));
		auto ff = &result.m;
		return Matrix(ff);
	}
	Matrix ToMatrixNoScale(void)
	{
		Matrix OutMatrix;
		return OutMatrix;
	}
};