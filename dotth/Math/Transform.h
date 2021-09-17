
#pragma once

#include "Float2.h"
#include "Float3.h"
#include "Float4.h"
#include "Matrix.h"

struct Transform 
{
public:
	Vector3F Scale{ 1.f, 1.f, 1.f };
	Vector3F WorldScale{ 1.f, 1.f, 1.f };
	Vector3F Rotation{ 0.f, 0.f, 0.f };
	Vector3F Position{ 0.f, 0.f, 0.f };	
	Matrix WorldMatrix;
	Matrix WorldMatrixNoScale;

	void SetScale(const Vector3F& value) { Scale = value; }
	void Scaling(const Vector3F& value) { Vector3F::Multiply(Scale, value, Scale); }
	void Scaling(const float& value) { Vector3F::Multiply(Scale, value, Scale); }
	void ScalingX(const float& value) { Scale.x *= value; }
	void ScalingY(const float& value) { Scale.y *= value; }
	void ScalingZ(const float& value) { Scale.z *= value; }
	const Vector3F& GetScale(void) { return Scale; }
	const Vector3F& GetWorldScale(void) { return WorldScale; }

	void SetRotation(const Vector3F& value) { Rotation = value; }
	void Rotate(const Vector3F& value) { Vector3F::Add(Rotation, value, Rotation); }
	void RotatePitch(const float& value) { Rotation.x += value; }
	void RotateYaw(const float& value) { Rotation.y += value; }
	void RotateRoll(const float& value) { Rotation.z += value; }
	const Vector3F& GetRotation(void) { return Rotation; }

	void SetPosition(const Vector3F& value) { Position = value; }
	void Translate(const Vector3F& value) { Vector3F::Add(Position, value, Position); }
	void TranslateX(const float& value) { Position.x += value; }
	void TranslateY(const float& value) { Position.y += value; }
	void TranslateZ(const float& value) { Position.z += value; }
	const Vector3F& GetPosition(void) { return Position; }

	void Update(const Transform* Parent = nullptr)
	{
		WorldScale = Scale;
		Float3 TmpPosition = Position;
		if (Parent != nullptr)
		{
			Vector3F::Multiply(Scale, Parent->WorldScale, WorldScale);
			Vector3F::Multiply(Position, Parent->WorldScale, TmpPosition);
		}
		Matrix scl = Matrix::Scaling(WorldScale);
		Matrix pitch = Matrix::RotatePitch(Rotation.x);
		Matrix yaw = Matrix::RotateYaw(Rotation.y);
		Matrix roll = Matrix::RotateRoll(Rotation.z);
		Matrix pos = Matrix::Translate(TmpPosition);
		if (Parent != nullptr)
			WorldMatrixNoScale = pitch * yaw * roll * pos * Parent->WorldMatrixNoScale;
		else
			WorldMatrixNoScale = pitch * yaw * roll * pos;
		WorldMatrix = scl * WorldMatrixNoScale;
	}

	Matrix GetWorldMatrix(void) const
	{
		return WorldMatrix;
	}
};