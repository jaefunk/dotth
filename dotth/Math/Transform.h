
#pragma once

struct Transform 
{
public:
	Vector3 Scale{ 1.f, 1.f, 1.f };
	Vector3 WorldScale{ 1.f, 1.f, 1.f };
	Vector3 Rotation{ 0.f, 0.f, 0.f };
	Vector3 Position{ 0.f, 0.f, 0.f };	
	Matrix WorldMatrix;
	Matrix WorldMatrixNoScale;

	void SetScale(float x, float y, float z) { Scale.x = x; Scale.y = y; Scale.z = z; }
	void SetScale(const Vector3& value) { Scale = value; }
	void Scaling(float value) { Vector3::Multiply(Scale, value, Scale); }
	void Scaling(const Vector3& value) { Vector3::Multiply(Scale, value, Scale); }
	const Vector3& GetScale(void) { return Scale; }
	const Vector3& GetWorldScale(void) { return WorldScale; }

	void SetRotation(const Vector3& value) { Rotation = value; }
	void Rotate(const Vector3& value) { Vector3::Add(Rotation, value, Rotation); }
	void RotatePitch(float value) { Rotation.x += value; }
	void RotateYaw(float value) { Rotation.y += value; }
	void RotateRoll(float value) { Rotation.z += value; }
	const Vector3& GetRotation(void) { return Rotation; }

	void SetPosition(const Vector3& value) { Position = value; }
	void Translate(const Vector3& value) { Vector3::Add(Position, value, Position); }
	const Vector3& GetPosition(void) { return Position; }

	void Update(const Transform* Parent = nullptr)
	{
		WorldScale = Scale;
		Vector3 TmpPosition = Position;
		if (Parent != nullptr)
		{
			Vector3::Multiply(Scale, Parent->WorldScale, WorldScale);
			Vector3::Multiply(Position, Parent->WorldScale, TmpPosition);
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