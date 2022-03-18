
#pragma once

using namespace dotth;
struct Transform 
{
public:
	vector3 Scale{ 1.f, 1.f, 1.f };
	vector3 WorldScale{ 1.f, 1.f, 1.f };
	vector3 Rotation{ 0.f, 0.f, 0.f };
	vector3 Position{ 0.f, 0.f, 0.f };	
	matrix WorldMatrix;
	matrix WorldMatrixNoScale;

	void SetScale(float x, float y, float z) { Scale.x = x; Scale.y = y; Scale.z = z; }
	void SetScale(const vector3& value) { Scale = value; }
	void Scaling(float value) { vector3::multiply(Scale, value, Scale); }
	void Scaling(const vector3& value) { vector3::multiply(Scale, value, Scale); }
	const vector3& GetScale(void) { return Scale; }
	const vector3& GetWorldScale(void) { return WorldScale; }

	void SetRotation(const vector3& value) { Rotation = value; }
	void Rotate(const vector3& value) { vector3::add(Rotation, value, Rotation); }
	void RotatePitch(float value) { Rotation.x += value; }
	void RotateYaw(float value) { Rotation.y += value; }
	void RotateRoll(float value) { Rotation.z += value; }
	const vector3& GetRotation(void) { return Rotation; }

	void SetPosition(const vector3& value) { Position = value; }
	void Translate(const vector3& value) { vector3::add(Position, value, Position); }
	const vector3& GetPosition(void) { return Position; }

	void Update(const Transform* Parent = nullptr)
	{
		WorldScale = Scale;
		vector3 TmpPosition = Position;
		if (Parent != nullptr)
		{
			vector3::multiply(Scale, Parent->WorldScale, WorldScale);
			vector3::multiply(Position, Parent->WorldScale, TmpPosition);
		}
		matrix scl = matrix::scaling(WorldScale);
		matrix pitch = matrix::rotate_pitch(Rotation.x);
		matrix yaw = matrix::rotate_yaw(Rotation.y);
		matrix roll = matrix::rotate_roll(Rotation.z);
		matrix pos = matrix::translate(TmpPosition);
		if (Parent != nullptr)
			WorldMatrixNoScale = pitch * yaw * roll * pos * Parent->WorldMatrixNoScale;
		else
			WorldMatrixNoScale = pitch * yaw * roll * pos;
		//if (Parent != nullptr)
		//	WorldMatrixNoScale = Parent->WorldMatrixNoScale * pos * roll * yaw * pitch;
		//else
		//	WorldMatrixNoScale = pos * roll * yaw * pitch;
		WorldMatrix = WorldMatrixNoScale * scl;
	}

	matrix GetWorldMatrix(void) const
	{
		return WorldMatrix;
	}
};